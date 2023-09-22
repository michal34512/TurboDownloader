#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>
#include <fstream>
#include <chrono>
#include <thread>
#include "Download.h"

namespace Download
{
	class GetHeader
	{
	public:
		static unsigned long long FileSize;
		static char* FileType;
		static DownloadArgs* arguments;
		static void GetTransferInfo(DownloadArgs& _arguments);
	};
}
