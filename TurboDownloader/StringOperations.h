#pragma once
#include <string>

namespace AdditionalTools
{
	class StringOperations
	{
	public:
		static std::string utf8_encode(const std::wstring& wstr);
		static std::wstring utf8_decode(const std::string& str);
	};
}