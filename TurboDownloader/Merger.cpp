#include "Merger.h"
#include "LogReporter.h"
#include "FileFetcher.h"
#include <fstream>
#include <filesystem>


namespace Download
{
	void Merger::Start(DownloadArgs& _arguments, int _StartAt)
	{
		endTh = false;
		arguments = _arguments;
		FilesToMerge.clear();
		NowMerging = _StartAt;
		OutputFile.open(arguments.OutputFilePath.c_str(), std::ios::out | std::ios::binary);
		OutputFile.rdbuf()->pubsetbuf(outBuffer, sizeof(outBuffer));
		if(!th.joinable())
			th = std::thread(Update);
	}
	void Merger::End()
	{
		OutputFile.close();
		endTh = true;
		if (th.joinable())
			th.join();	
	}
	void Merger::AddFileToMerge(int _IndexInQueue)
	{
		FilesToMerge.push_back(_IndexInQueue);
	}
	void Merger::Update()
	{
		while (!endTh)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (size_t i = 0; i < FilesToMerge.size(); i++)
			{
				if (NowMerging == FilesToMerge[i])
				{
					if (MergeFile(NowMerging)) {
						FilesToMerge.erase(FilesToMerge.begin() + i);
						NowMerging++;
					}
				}
			}
		}
	}
	bool Merger::MergeFile(int _index)
	{
		//Merging
		std::fstream fileToMerge;
		fileToMerge.rdbuf()->pubsetbuf(inBuffer, sizeof(inBuffer));
		OutputFile.rdbuf()->pubsetbuf(outBuffer, sizeof(outBuffer));
		std::wstring path = AdditionalTools::FileFetcher::GetPatchByIndexInQueue(arguments, _index);
		fileToMerge.open(path.c_str(), std::ios::in | std::ios::binary);

		if (fileToMerge.good())
		{
			fileToMerge.seekg(0, std::ios::end);
			std::streampos input_length = fileToMerge.tellg();
			fileToMerge.seekg(0, std::ios::beg);

			// Create a buffer of appropriate size
			std::vector<char> buffer(input_length);

			// Read the contents of the source file into the buffer
			fileToMerge.read(buffer.data(), input_length);

			// Save the contents of the buffer to the destination file
			OutputFile.write(buffer.data(), input_length);

			fileToMerge.close();

			// Attempt to delete the file
			DeleteFile(LPCTSTR(path.c_str()));
			return true;
		}
		else LogReporter::Error("Error while opening temporary file");



		return false;
	}
	bool Merger::IsMergning()
	{
		return FilesToMerge.size() != 0;
	}
	std::vector<int> Merger::FilesToMerge;
	std::thread Merger::th;
	bool Merger::endTh = false;
	std::fstream Merger::OutputFile;
	char Merger::inBuffer[1000000];
	char Merger::outBuffer[1000000];
	int Merger::NowMerging = 0;
	DownloadArgs& Merger::arguments = *(new DownloadArgs());

}