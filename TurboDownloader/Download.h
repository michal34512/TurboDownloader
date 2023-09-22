#pragma once
#include <iostream>

namespace Download {
	struct DownloadArgs
	{
	public:
		DownloadArgs() = default;
		std::string URL;
		std::wstring InputHeaderFilePath;
		std::wstring CookieFilePath;
		std::wstring OutputFilePath = L"Output.mp4";
		std::wstring Prefix = L"_"; //character added to temporary output files "Output.mp4" -> "_Output.mp4"
		unsigned int DownloadRate = 30;
		unsigned long long SinglePartSize = 10000000ULL;
		long LowSpeedLimit = 10L;
		long LowSpeedTime = 30L;
		std::string UserAgent = "Mozilla/5.0 (Linux; Linux x86_64) Gecko/20100101 Firefox/49.3";
		bool Verbose = false;
	};
	enum DownloadStatus {
		Ok,
		Error,
		LastFile
	};
	class Download
	{
	protected:
		bool isDownloading = false;
		DownloadArgs arguments;
	public:
		/// <summary>
		/// Function that starts download
		/// </summary>
		/// <returns>True when download is done</returns>
		virtual void Start(DownloadArgs _arguments) = 0;

		/// <summary>
		/// Function that should be called in main loop
		/// </summary>
		/// <returns>True when download is done</returns>
		virtual bool Update() = 0;

		/// <summary>
		/// Function that returns progress of the download
		/// </summary>
		/// <returns>True when download is done</returns>
		virtual float UpdateProgress() = 0;
	};
}
