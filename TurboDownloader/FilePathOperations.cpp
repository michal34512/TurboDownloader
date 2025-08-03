#include "FilePathOperations.h"
#include <Windows.h>
#include <algorithm>

namespace AdditionalTools {
    std::wstring FilePathOperations::GetExecutableDirectory(const wchar_t* _zeroArg) {
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(nullptr, buffer, MAX_PATH);

        std::wstring executablePath(buffer);

        size_t lastSlashPos = executablePath.find_last_of(L"\\/");
        if (lastSlashPos != std::wstring::npos) {
            exeDir = executablePath.substr(0, lastSlashPos);
            return exeDir;
        }

        return L"";
    }
    std::wstring FilePathOperations::GetFilenameFromPath(const std::wstring& _path) {
        size_t lastSlashPos = _path.find_last_of(L"/\\");
        if (lastSlashPos != std::wstring::npos) {
            return _path.substr(lastSlashPos + 1);
        }
        return _path;
    }
    std::wstring FilePathOperations::GetAbsuluteFilePath(const std::wstring& _path) {
        if (_path.length() >= 2 && _path[1] == L':' &&
            ((_path[2] == L'\\') || (_path[2] == L'/')))
        {
            return _path;
        }

        return FilePathOperations::exeDir + L"\\" + _path;
    }
    std::vector<std::wstring> FilePathOperations::GetFilesStartingWithPrefix(const std::wstring& _directory, const std::wstring& _prefix)
    {
       std::vector<std::wstring> matchingFiles;

        WIN32_FIND_DATA findData;
        HANDLE hFind = FindFirstFile((_directory + L"\\*").c_str(), &findData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 &&
                    wcsncmp(findData.cFileName, _prefix.c_str(), _prefix.size()) == 0)
                {
                    matchingFiles.push_back(findData.cFileName);
                }
            } while (FindNextFile(hFind, &findData));

            FindClose(hFind);
        }
        //Sort by length
        std::sort(matchingFiles.begin(), matchingFiles.end(), [](const std::wstring& a, const std::wstring& b) {return a.length() < b.length(); });
        return matchingFiles;
    }
    std::vector<std::wstring> FilePathOperations::GetFilesStartingWithPrefixFullPath(std::wstring _directory, const std::wstring& _prefix)
    {
        if (!_directory.empty() && _directory.back() != L'\\') {
            _directory += L'\\';
        }
        std::vector<std::wstring> res = GetFilesStartingWithPrefix(_directory, _prefix);
        for (auto& i : res)
        {
            i = _directory + i;
        }
        return res;
    }
    std::wstring FilePathOperations::exeDir;
}