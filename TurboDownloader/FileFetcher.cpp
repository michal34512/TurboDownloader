#include "FileFetcher.h"
#include "LogReporter.h"
#include <fstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
namespace AdditionalTools
{	
	std::string FileFetcher::lowerCaseString(std::string _string)
	{
		for (size_t i = 0; _string[i]; i++) {
			_string[i] = tolower(_string[i]);
		}
		return _string;
	}
	void FileFetcher::GetHeadersFromFile(CURL* _cHandle, std::wstring _HeaderFilePath, unsigned long long _DownRange, unsigned long long _UpRange)
	{
		std::string line;
		std::fstream InHeaderFile;
		InHeaderFile.open(_HeaderFilePath, std::ios::in | std::ios::binary);
		if (!InHeaderFile.good()) {
			return;
		}
		struct curl_slist* chunk = NULL;
		while (!InHeaderFile.eof())
		{
			getline(InHeaderFile, line);
			std::string lowerCaseLine = lowerCaseString(line);
			if (lowerCaseLine.find("range") == std::string::npos||(_DownRange == 0 && _UpRange == 0)) {
				chunk = curl_slist_append(chunk, line.c_str());
				continue;
			}
			std::string modifiedHeader = line.substr(0, line.find(":") + 1);
			modifiedHeader += " bytes=" + std::to_string(_DownRange) + "-" + std::to_string(_UpRange);
			chunk = curl_slist_append(chunk, modifiedHeader.c_str());
		}
		
		curl_easy_setopt(_cHandle, CURLOPT_HTTPHEADER, chunk);
	}
	void FileFetcher::TemporaryFileCleanup(Download::DownloadArgs& _arguments)
	{
		const std::wstring targetPattern = _arguments.Prefix;

		for (const auto& entry : fs::directory_iterator(GetDirPath(_arguments))) {
			if (fs::is_regular_file(entry) && fs::path(entry).filename().wstring().find(targetPattern) == 0) {
				fs::remove(entry.path());
			}
		}
	}
	std::wstring FileFetcher::GetDirPath(Download::DownloadArgs _arguments)
	{
		size_t i = _arguments.OutputFilePath.size() - 1;
		for (; i >= 0; i--)
			if (_arguments.OutputFilePath[i] == L'\\')
				break;
		return _arguments.OutputFilePath.substr(0, i) + L"\\";
	}
	std::wstring FileFetcher::GetPatchByIndexInQueue(Download::DownloadArgs _arguments, int _IndexInQueue)
	{
		std::wstring parsedIndex = _IndexInQueue < 0 ? L"*" : std::to_wstring(_IndexInQueue);

		size_t i = _arguments.OutputFilePath.size() - 1;
		for (; i >= 0; i--)
			if (_arguments.OutputFilePath[i] == L'\\')
				break;
		return _arguments.OutputFilePath.substr(0, i) + L"\\" + _arguments.Prefix + parsedIndex + _arguments.OutputFilePath.substr(i + 1, _arguments.OutputFilePath.size() - i);
	}
}
