#pragma once
#define CURL_STATICLIB
#include "GetHeader.h"
#include "LogReporter.h"
#include "FileFetcher.h"

namespace Download
{
	void GetHeader::GetTransferInfo(DownloadArgs& _arguments)
	{
		arguments = &_arguments;
		CURL* curl = curl_easy_init();
		std::fstream HeadersFile;
		HeadersFile.open(arguments->InputHeaderFilePath.c_str(), std::ios::in | std::ios::binary);

		if (curl && HeadersFile.good()) {
			curl_easy_setopt(curl, CURLOPT_URL, arguments->URL.c_str());
			AdditionalTools::FileFetcher::GetHeadersFromFile(curl, arguments->InputHeaderFilePath);
			HeadersFile.close();
			curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 102400L);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, arguments->UserAgent);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 1L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);//certificate fix
			curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
			CURLcode code = curl_easy_perform(curl);
			
			if (code == CURLcode::CURLE_OK)
			{
				curl_off_t contentLength;
				curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &contentLength);
				curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &FileType);
				FileSize = contentLength;
			}
			else{
				LogReporter::Error("Problem with connection to the server");
			}
		}
		else if (!curl) {
			LogReporter::Error("Problem with curl");
		}
		else
		{
			LogReporter::Error("Cannot open header file");
		}
	}
	DownloadArgs* GetHeader::arguments;
	unsigned long long GetHeader::FileSize;
	char* GetHeader::FileType;
}
