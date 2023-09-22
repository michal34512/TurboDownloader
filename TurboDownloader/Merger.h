#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include "Download.h"

namespace Download 
{
	static class Merger {
		//Thread
		static std::thread th;
		static bool endTh;

		static std::vector<int> FilesToMerge;
		static std::fstream OutputFile;
		static char inBuffer[1000000]; //1mb
		static char outBuffer[1000000]; //1mb
		static int NowMerging;
		static DownloadArgs& arguments;

		static void Update();
		static bool MergeFile(int _index);
	public:
		static void Start(DownloadArgs& _arguments, int _StartAt = 0);
		static void End();
		static void AddFileToMerge(int _IndexInQueue);
		static bool IsMergning();
	};
}
