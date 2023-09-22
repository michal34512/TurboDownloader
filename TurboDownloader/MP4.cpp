#include "MP4.h"
#include <curl/curl.h>
#include "LogReporter.h"
#include "GetHeader.h"
#include "FileFetcher.h"
#include "Merger.h"
#include "StringOperations.h"

using namespace AdditionalTools;

namespace Download
{
	size_t MP4::WriteData(char* ptr, size_t size, size_t nmemb, void* outfile)
	{
		std::fstream* out = static_cast<std::fstream*>(outfile);
		size_t nbytes = size * nmemb;
		out->write(ptr, nbytes);
		return nbytes;
	}

	int MP4::ProgressFunction(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
	{
		SinglePart* out = static_cast<SinglePart*>(ptr);
		out->AlreadyDownloaded = (unsigned long long)NowDownloaded;
		return 0;
	}

	DownloadStatus MP4::NewTransfer(int _IndexInArray, int _IndexInQueue)
	{
		unsigned long long downBound = _IndexInQueue * arguments.SinglePartSize;
		unsigned long long upBound = ((_IndexInQueue + 1) * arguments.SinglePartSize) - 1;
		
		if (downBound > GetHeader::FileSize) return DownloadStatus::LastFile;
		if (upBound > GetHeader::FileSize) upBound = GetHeader::FileSize;
		
		CURL* handle;
		handle = curl_easy_init();
		PartsArray[_IndexInArray].Handle = handle;
		PartsArray[_IndexInArray].IndexInQueue = _IndexInQueue;
		PartsArray[_IndexInArray].ExpectedSize = upBound - downBound + 1;
		if (arguments.Verbose)
		{
			LogReporter::Log("Starting partial transfer from: " + std::to_string(downBound) + " to: " + std::to_string(upBound) + " expected size: " + std::to_string(PartsArray[_IndexInArray].ExpectedSize));
		}
		if (!handle)
		{
			LogReporter::Error("Problem with curl");
			return DownloadStatus::Error;
		}
		curl_easy_setopt(handle, CURLOPT_NOPROGRESS, FALSE); //Disable inter progress meter
		curl_easy_setopt(handle, CURLOPT_PROGRESSFUNCTION, ProgressFunction); //Enable custom progress meter
		curl_easy_setopt(handle, CURLOPT_PROGRESSDATA, &PartsArray[_IndexInArray]);

		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteData);//send all data to this function
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, false);//certificate fix
		curl_easy_setopt(handle, CURLOPT_USERAGENT, arguments.UserAgent);
		curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(handle, CURLOPT_FTP_SKIP_PASV_IP, 1L);
		curl_easy_setopt(handle, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(handle, CURLOPT_LOW_SPEED_LIMIT, arguments.LowSpeedLimit);
		curl_easy_setopt(handle, CURLOPT_LOW_SPEED_TIME, arguments.LowSpeedTime);
		if (arguments.CookieFilePath.size() > 0)
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, arguments.CookieFilePath.c_str());
		if (arguments.InputHeaderFilePath.size() > 0)
			FileFetcher::GetHeadersFromFile(handle, arguments.InputHeaderFilePath, downBound, upBound);
		//Preparing URL
		curl_easy_setopt(handle, CURLOPT_URL, arguments.URL.c_str());

		PartsArray[_IndexInArray].OutFile.open(FileFetcher::GetPatchByIndexInQueue(arguments, _IndexInQueue), std::ios::out | std::ios::binary);
		if (PartsArray[_IndexInArray].OutFile.good())
		{
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, &PartsArray[_IndexInArray].OutFile);
			curl_multi_add_handle(MultiManager, handle);
			return DownloadStatus::Ok;
		}
		else {
			LogReporter::Error("Problem with output file");
		}
		LogReporter::Error("Creating new tranfer failed");
		return DownloadStatus::Error;
	}
	int MP4::GetIndexInPartsArrayByHandle(CURL* _handle)
	{
		for (int index = 0; index < arguments.DownloadRate; index++)
			if (PartsArray[index].Handle == _handle)
			{
				return index;
			}
		return -1;
	}
	// OVERRIDED METHODS
	void MP4::Start(DownloadArgs _arguments)
	{
		arguments = _arguments;

		if (arguments.Verbose)
		{
			LogReporter::Log("Data: ");
			LogReporter::Log("URL: " + arguments.URL);
			LogReporter::Log("Header file: " + StringOperations::utf8_encode(arguments.InputHeaderFilePath));
			LogReporter::Log("Cookie file: " + StringOperations::utf8_encode(arguments.CookieFilePath));
			LogReporter::Log("Output file: " + StringOperations::utf8_encode(arguments.OutputFilePath));
			LogReporter::Log("Prefix: " + StringOperations::utf8_encode(arguments.Prefix));
			LogReporter::Log("Download rate: " + std::to_string(arguments.DownloadRate));
			LogReporter::Log("Single part size: " + std::to_string(arguments.SinglePartSize));
			LogReporter::Log("Low speed limit: " + std::to_string(arguments.LowSpeedLimit));
			LogReporter::Log("Low speed time: " + std::to_string(arguments.LowSpeedTime));
			LogReporter::Log("User agent: " + arguments.UserAgent);
		}

		curl_global_init(CURL_GLOBAL_ALL); //init the curl session
		MultiManager = curl_multi_init(); //init curl multi
		curl_multi_setopt(MultiManager, CURLMOPT_MAXCONNECTS, (long)arguments.DownloadRate); //setting max rate
		PartsArray = new SinglePart[arguments.DownloadRate];
		for (int i = 0; i < arguments.DownloadRate; i++)
		{
			NewTransfer(i, i);
			LastIndexInQueue++;
		}
		Merger::Start(arguments);
		isDownloading = true;
	}
	bool MP4::Update()
	{
		if (!isDownloading) return false;
		curl_multi_perform(MultiManager, &StillAliveTransferCount);
		while (MultiMessages = curl_multi_info_read(MultiManager, &MuliMessagesLeft))
		{
			if (MultiMessages->msg == CURLMSG_DONE)
			{
				CURL* finishedDownload = MultiMessages->easy_handle;
				int index = GetIndexInPartsArrayByHandle(finishedDownload);
				curl_multi_remove_handle(MultiManager, finishedDownload);
				curl_off_t downloadedDataSize;
				curl_easy_getinfo(finishedDownload, CURLINFO_SIZE_DOWNLOAD_T, &downloadedDataSize);
				
				if (index == -1)
				{
					LogReporter::Error("Finished transfer had unidentified index");
					curl_easy_cleanup(finishedDownload);
				}
				else
				{
					PartsArray[index].OutFile.close();
					if (downloadedDataSize <= PartsArray[index].ExpectedSize+1 && downloadedDataSize >= PartsArray[index].ExpectedSize - 1)
					{
						Merger::AddFileToMerge(PartsArray[index].IndexInQueue);

						//Starting next transfer
						PartsArray[index] = SinglePart();
						NewTransfer(index, LastIndexInQueue);
						LastIndexInQueue++;
						curl_easy_cleanup(finishedDownload);

						//Checking if whole download is completed
						for (int i = 0; i < arguments.DownloadRate; i++)
						{
							if (PartsArray[i].IndexInQueue != -1)
								return false;
						}
					}
					else{
						LogReporter::Warning("Transfer number " + std::to_string(PartsArray[index].IndexInQueue) + " failed");
						LogReporter::Warning("Resetting");
						NewTransfer(index, PartsArray[index].IndexInQueue);
						curl_easy_cleanup(finishedDownload);
					}
				}
			}
		}
		if (StillAliveTransferCount != 0)
		{
			curl_multi_wait(MultiManager, NULL, 0, 1000, NULL);
		}
		else if (!Merger::IsMergning()) { //ending merger
			Merger::End();
			isDownloading = false;
			return true;
		}

		return false;
	}
	float MP4::UpdateProgress()
	{
		unsigned long long totalDownloaded = 0;
		if (LastIndexInQueue >= arguments.DownloadRate) totalDownloaded = (LastIndexInQueue - arguments.DownloadRate) * arguments.SinglePartSize;
		for (int i = 0; i < arguments.DownloadRate; i++)
		{
			totalDownloaded += PartsArray[i].AlreadyDownloaded;
		}
		return (float)totalDownloaded / GetHeader::FileSize;
	}
}