#include "StringOperations.h"
#include <codecvt>
#include <windows.h>
#include <cwctype>

namespace AdditionalTools
{
	std::string StringOperations::utf8_encode(const std::wstring& wstr)
	{
		if (wstr.empty()) return std::string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}
	std::wstring StringOperations::utf8_decode(const std::string& str) {
		if (str.empty()) return std::wstring();
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}
	std::string StringOperations::remove_whitespace_characters(std::string& str) {
		str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return (std::isspace(x)); }), str.end());
		return str;
	}

	std::wstring StringOperations::remove_whitespace_characters(std::wstring& wstr) {
		wstr.erase(std::remove_if(wstr.begin(), wstr.end(), [](wchar_t x) { return std::iswspace(x); }), wstr.end());
		return wstr;
	}

}