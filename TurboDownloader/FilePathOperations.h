#pragma once
#include <iostream>
#include <vector>

namespace AdditionalTools{
	class FilePathOperations
	{
	public:
		static std::wstring exeDir;
		static std::wstring GetExecutableDirectory(const wchar_t* _zeroArg);
		static std::wstring GetFilenameFromPath(const std::wstring& _path);
		static std::wstring GetAbsuluteFilePath(const std::wstring& _path);
		static std::vector<std::wstring> GetFilesStartingWithPrefix(const std::wstring& _directory, const std::wstring& _prefix);
		static std::vector<std::wstring> GetFilesStartingWithPrefixFullPath(std::wstring _directory, const std::wstring& _prefix);
	};
}
