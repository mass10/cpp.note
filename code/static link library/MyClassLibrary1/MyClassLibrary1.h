#pragma once

#include <string>

namespace abcde1
{
	std::string hello();

	class MyUtilClass1
	{
	public:
		static std::string trim(const char* s);
		static std::wstring trim(const wchar_t* s);
	private:
		MyUtilClass1();
	};
}