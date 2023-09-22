#pragma once
#include "Download.h"
#include <curl/curl.h>
#include <fstream>

namespace Download
{
	class MP2T : public Download
	{
		int LastIndexInQueue = 1;
		int DownloadedSegmentCount = 0;
		unsigned int SegmentCount = 0;

		// Curl
		CURLM* MultiManager;
		CURLMsg* MultiMessages;
		int StillAliveTransferCount;
		int MuliMessagesLeft;

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
		unsigned int GetPartFileCount();
		void FixURL();
	public:
		// OVERRIDED METHODS
		void Start(DownloadArgs _arguments);
		bool Update();
		float UpdateProgress();

		static size_t WriteData(char* ptr, size_t size, size_t nmemb, void* outfile);
		static int ProgressFunction(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
		static size_t GetSegCountURLWriteFunc(char* ptr, size_t size, size_t nmemb, unsigned int* out);
	};
}