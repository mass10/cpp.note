#pragma once

#include <tchar.h>
#include <string>
#include <sstream>

class logger
{
public:
	logger();
	logger(const _TCHAR* something);
	logger(const std::wstring& something);
	logger(const std::wstringstream& something);
	~logger();
private:
};

