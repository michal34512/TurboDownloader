#pragma once
#include <curl/curl.h>
#include <iostream>
#include "Download.h"

namespace AdditionalTools 
{
	class FileFetcher
	{
	public:
		static std::string lowerCaseString(std::string _string);
		static void GetHeadersFromFile(CURL* _cHandle, std::wstring _HeaderFilePath, unsigned long long _DownRange = 0, unsigned long long _UpRange = 0);
		static void TemporaryFileCleanup(Download::DownloadArgs& _arguments);
		static std::wstring GetDirPath(Download::DownloadArgs _arguments);
		static std::wstring GetPatchByIndexInQueue(Download::DownloadArgs _arguments, int _IndexInQueue = -1);
	};
}
