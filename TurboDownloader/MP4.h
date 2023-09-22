#pragma once
#include "Download.h"
#include <fstream>
#include <curl/curl.h>


namespace Download
{
	class MP4 : public Download
	{
		int LastIndexInQueue = 0;

		// Curl
		CURLM* MultiManager;
		CURLMsg* MultiMessages;
		int StillAliveTransferCount;
		int MuliMessagesLeft;

		// File parts
		class SinglePart
		{
		public:
			CURL* Handle;
			int IndexInQueue = -1;
			std::fstream OutFile;
			unsigned long long AlreadyDownloaded = 0;
			unsigned long long ExpectedSize = 0;
		};
		SinglePart* PartsArray;

		DownloadStatus NewTransfer(int _IndexInArray, int _IndexInQueue);
		int GetIndexInPartsArrayByHandle(CURL* _handle);
	public:
		// OVERRIDED METHODS
		void Start(DownloadArgs _arguments);
		bool Update();
		float UpdateProgress();

		static size_t WriteData(char* ptr, size_t size, size_t nmemb, void* outfile);
		static int ProgressFunction(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
	};
}