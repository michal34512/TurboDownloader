#include "MP2T.h"
#include <curl/curl.h>
#include <thread>
#include <chrono>

#include "LogReporter.h"
#include "FileFetcher.h"
#include "Merger.h"
#include "StringOperations.h"
#include "FFMpeg.h"

using namespace AdditionalTools;

namespace Download
{
	size_t MP2T::WriteData(char* ptr, size_t size, size_t nmemb, void* outfile)
	{
		std::fstream* out = static_cast<std::fstream*>(outfile);
		size_t nbytes = size * nmemb;
		out->write(ptr, nbytes);
		return nbytes;
	}

	int MP2T::ProgressFunction(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
	{
		MP2T::SinglePart* out = static_cast<MP2T::SinglePart*>(ptr);
		out->AlreadyDownloaded = (unsigned long long)NowDownloaded;
		return 0;
	}
	size_t MP2T::GetSegCountURLWriteFunc(char* ptr, size_t size, size_t nmemb, unsigned int* out)
	{
		std::string data = ptr;
		std::cout << data << std::endl << std::endl << std::endl;
		if (data.rfind("#EXT-X-ENDLIST") == std::string::npos) return size * nmemb;
		if (data.rfind("\x0a") == std::string::npos) return size * nmemb;
			
		size_t firstChar = data.rfind("seg-");
		if (firstChar == std::string::npos) return size * nmemb;
		firstChar += 4;
		size_t lastChar = data.find("-", firstChar);
		if (lastChar == std::string::npos) return size * nmemb;
		*out = atoi(data.substr(firstChar, lastChar - firstChar).c_str());
			
		return size * nmemb;
	}
	unsigned int MP2T::GetPartFileCount()
	{
		unsigned int* segCount = new unsigned int(0UL);
		//Preparing URL
		std::string indexURL = arguments.URL;
		if (indexURL.rfind("seg-{}") == std::string::npos || indexURL.rfind(".ts") == std::string::npos) return 0;
		indexURL.replace(indexURL.rfind("seg-{}"), 6, "index");
		indexURL = indexURL.replace(indexURL.rfind(".ts"), 3, ".m3u8");
		if (arguments.Verbose)
		{
			LogReporter::Log("Trying to scrap file count. Index URL: " + indexURL);
		}

		CURL* curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, indexURL.c_str());
			curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 102400L);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, arguments.UserAgent);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
			curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 1L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);//certificate fix
			if (arguments.CookieFilePath.size() > 0)
				curl_easy_setopt(curl, CURLOPT_COOKIEFILE, arguments.CookieFilePath);
			if (arguments.InputHeaderFilePath.size() > 0)
				FileFetcher::GetHeadersFromFile(curl, arguments.InputHeaderFilePath);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetSegCountURLWriteFunc);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, segCount);
			CURLcode result = curl_easy_perform(curl);
			int RetrySec = 3;
			for (int i = 0; i < RetrySec; i++)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				if (*segCount != 0)
				{
					curl_easy_cleanup(curl);
					return *segCount;
				}
			}
		}
		return 0;
	}
	void MP2T::FixURL()
	{
		//Prepare URL   eg:  /seg-1-v1-a1.ts  ->  /seg-{}-v1-a1.ts
		size_t f = arguments.URL.rfind("seg-") + 4; //finds last occurance
		if (f != std::string::npos)
		{
			size_t j = 0;
			for (; j < arguments.URL.size(); j++)
				if (arguments.URL[j + f] == '-') break;
			if (j + 1 != arguments.URL.size())
			{
				arguments.URL.replace(f, j, "{}");
			}
		}
		//Checking if URL is valid
		if (arguments.URL.rfind("{}") == std::string::npos) //finds last occurance
		{
			LogReporter::Error("URL is not valid!");
			return;
		}
	}
	DownloadStatus MP2T::NewTransfer(int _IndexInArray, int _IndexInQueue)
	{
		//Checking for end
		if (SegmentCount != 0 && SegmentCount <= _IndexInQueue) return DownloadStatus::LastFile; // END

		CURL* handle;
		handle = curl_easy_init();
		PartsArray[_IndexInArray].Handle = handle;
		PartsArray[_IndexInArray].IndexInQueue = _IndexInQueue;

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
		curl_easy_setopt(handle, CURLOPT_USERAGENT, arguments.UserAgent.c_str());
		curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(handle, CURLOPT_FTP_SKIP_PASV_IP, 1L);
		curl_easy_setopt(handle, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(handle, CURLOPT_LOW_SPEED_LIMIT, arguments.LowSpeedLimit);
		curl_easy_setopt(handle, CURLOPT_LOW_SPEED_TIME, arguments.LowSpeedTime);
		if (arguments.CookieFilePath.size() > 0)
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, arguments.CookieFilePath.c_str());
		if (arguments.InputHeaderFilePath.size() > 0)
			FileFetcher::GetHeadersFromFile(handle, arguments.InputHeaderFilePath.c_str());
		//Preparing URL
		if (arguments.URL.rfind("{}") == std::string::npos) {
			LogReporter::Error("Invalid URL: "+ arguments.URL);
			return DownloadStatus::Error;
		}
		std::string URLCopy = arguments.URL;
		URLCopy.replace(arguments.URL.rfind("{}"), 2, std::to_string(_IndexInQueue));
		if (arguments.Verbose)
		{
			LogReporter::Log("Starting partial transfer number: " + std::to_string(_IndexInQueue) + ", URL: " + URLCopy);
		}
		curl_easy_setopt(handle, CURLOPT_URL, URLCopy.c_str());
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
	int MP2T::GetIndexInPartsArrayByHandle(CURL* _handle)
	{
		for (int index = 0; index < arguments.DownloadRate; index++)
			if (PartsArray[index].Handle == _handle)
			{
				return index;
			}
		return -1;
	}
	
	// OVERRIDED METHODS
	void MP2T::Start(DownloadArgs _arguments)
	{
		LastIndexInQueue = 1;
		arguments = _arguments;

		FixURL();
		SegmentCount = GetPartFileCount();

		if (arguments.Verbose)
		{
			LogReporter::Log("Data: ");
			LogReporter::Log("URL: " + arguments.URL);
			LogReporter::Log("Header file: " + StringOperations::utf8_encode(arguments.InputHeaderFilePath));
			LogReporter::Log("Cookie file: " + StringOperations::utf8_encode(arguments.CookieFilePath));
			LogReporter::Log("Output file: " + StringOperations::utf8_encode(arguments.OutputFilePath));
			LogReporter::Log("Prefix: " + StringOperations::utf8_encode(arguments.Prefix));
			LogReporter::Log("Download rate: " + std::to_string(arguments.DownloadRate));
			LogReporter::Log("Low speed limit: " + std::to_string(arguments.LowSpeedLimit));
			LogReporter::Log("Low speed time: " + std::to_string(arguments.LowSpeedTime));
			LogReporter::Log("User agent: " + arguments.UserAgent);
			LogReporter::Log("Received data: ");
			LogReporter::Log("Segment count: " + std::to_string(SegmentCount));
		}
		
		curl_global_init(CURL_GLOBAL_ALL); //init the curl session
		MultiManager = curl_multi_init(); //init curl multi
		curl_multi_setopt(MultiManager, CURLMOPT_MAXCONNECTS, (long)arguments.DownloadRate); //setting max rate
		PartsArray = new SinglePart[arguments.DownloadRate];
		for (int i = 1; i < arguments.DownloadRate; i++)
		{
			NewTransfer(i, i);
			LastIndexInQueue++;
		}
		Merger::Start(arguments, 1);
		isDownloading = true;
	}
	bool MP2T::Update()
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
					curl_off_t expectedDataSize;
					curl_easy_getinfo(finishedDownload, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &expectedDataSize);
					if ((SegmentCount == 0 && downloadedDataSize > 1000) || (SegmentCount != 0 && expectedDataSize == downloadedDataSize))
					{
						DownloadedSegmentCount++;
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
					else if (SegmentCount == 0)
					{
						DeleteFile(LPCTSTR(FileFetcher::GetPatchByIndexInQueue(arguments, PartsArray[index].IndexInQueue).c_str()));
					}
					else {
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
			FFMpeg::Start(arguments.OutputFilePath);
			isDownloading = false;
			return true;
		}
		

		return false;
	}
	float MP2T::UpdateProgress()
	{
		return (float)DownloadedSegmentCount / SegmentCount;
	}
}