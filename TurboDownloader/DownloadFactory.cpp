#include "DownloadFactory.h"
#include "LogReporter.h"
#include "GetHeader.h"
#include "Merger.h"
#include "MP4.h"
#include "MP2T.h"

namespace Download
{
	Download* DownloadFactory::GetDownload()
	{
		return createdDownload;
	}
	void DownloadFactory::CreateDownload()
	{
		LogReporter::Log("Starting transfer...");
		GetHeader::GetTransferInfo(arguments);
		if (strstr(GetHeader::FileType, "MP2T") != nullptr)
		{
			createdDownload = new MP2T();
		}
		else {
			createdDownload = new MP4();
		}
	}
	void DownloadFactory::Start()
	{
		std::cout << "a";
		if(GetDownload()!=nullptr)
			GetDownload()->Start(arguments);
		std::cout << "b";
	}
	void DownloadFactory::Update()
	{
		if (GetDownload() != nullptr)
		{
			if (GetDownload()->Update())
			{
				LogReporter::Log("Transfer finished");
				createdDownload = nullptr;
			}
		}
	}
	int DownloadFactory::GetProgressPercentage()
	{
		if (GetDownload() != nullptr)
		{
			int value = int(100 * GetDownload()->UpdateProgress());
			if (value > 100) value = 100;
			else if (value < 0) value = 0;
			return value;
		}
		return 0;
	}
	Download* DownloadFactory::createdDownload;
	DownloadArgs DownloadFactory::arguments;
}
