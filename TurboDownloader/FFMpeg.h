#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

#include "LogReporter.h"
namespace AdditionalTools
{
	static class FFMpeg
	{
	public:
		static void Start(std::wstring _OutputPath);
	};
}
