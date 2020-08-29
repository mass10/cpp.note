#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include <time.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class timestamp {
public:
	timestamp() {
		struct tm tm;
		time_t t = time(NULL);
		localtime_r(&t, &tm);
		char buffer[64];
		sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		this->s = buffer;
	}
	operator const char* () const {
		return this->s.c_str();
	}
private:
	std::string s;
};

int main() {
	std::cout << timestamp() << "\n";
	return 0;
}

/*
// ConsoleApplication2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>
#include <tchar.h>

std::string GetCurrentTimestamp()
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	char buffer[40];
	sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

int main()
{
	std::string timestamp = GetCurrentTimestamp();
	std::cout << timestamp << "\n";
}

*/

