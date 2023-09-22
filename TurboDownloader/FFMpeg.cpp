#include "FFmpeg.h"
#include "FilePathOperations.h"
#include "StringOperations.h"

namespace AdditionalTools
{
	void FFMpeg::Start(std::wstring _OutputPath)
	{
		std::string stringOutputFilename = StringOperations::utf8_encode(FilePathOperations::GetFilenameFromPath(_OutputPath));

		LogReporter::Log("searching for FFMPEG...");
		std::remove("EXIST.txt");
		system("where /q ffmpeg");
		system("IF ERRORLEVEL 1 (echo EXIST > EXIST.txt)");
		std::fstream Exist;
		Exist.open("EXIST.txt", std::ios::in);
		if (!Exist.good())
		{
			LogReporter::Log("FFMPEG found, reconverting file...");
			std::rename(stringOutputFilename.c_str(), ("FFMPEG_"+stringOutputFilename).c_str());
			std::fstream MList;
			MList.open("MList.txt", std::ios::out);
			MList << "file FFMPEG_" + stringOutputFilename;
			MList.close();
			system(("ffmpeg -y -f concat -safe 0 -i MList.txt -bsf:a aac_adtstoasc -c copy " + stringOutputFilename).c_str());
			std::remove("MList.txt");
			std::remove(("FFMPEG_" + stringOutputFilename).c_str());
			LogReporter::Log("File reconverted, task successful...");

		}
		else {
			LogReporter::Warning("FFMPEG not found, but task is still successful...");
			Exist.close();
			std::remove("EXIST.txt");
		}
	}
}
