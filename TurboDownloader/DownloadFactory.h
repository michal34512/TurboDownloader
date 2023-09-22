#pragma once
#include "Download.h"

namespace Download
{
	class DownloadFactory
	{
		static Download* createdDownload;
		
	public:
		static DownloadArgs arguments;
		static Download* GetDownload();
		static void CreateDownload();
		static void Start();
		static void Update();
		static int GetProgressPercentage();
	};
}
