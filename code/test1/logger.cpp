#include "logger.h"

#include <sstream>
#include <tchar.h>
#include <string>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <clocale>
#include <Windows.h>
#include <tchar.h>
#include <string.h>
#include <locale.h>
#include <string>
#include <sstream>
#include <codecvt>


std::wstring _get_timestamp() {

	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR timestamp[40] = _T("");
	wsprintf(timestamp, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return timestamp;
}

logger::logger() {

}

logger::logger(const _TCHAR* something)
{
	const _TCHAR* path = _T("myapp.log");
	std::wofstream ofs;
	//ofs.imbue(std::locale("Japanese", LC_COLLATE));
	//ofs.imbue(std::locale("Japanese", LC_CTYPE));
	ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
	ofs.open(path, std::ios::app);
	ofs << _get_timestamp() << " [TRACE] " << something << std::endl;
	ofs.close();
}

logger::logger(const std::wstring& something)
{
	const _TCHAR* path = _T("myapp.log");
	std::wofstream ofs;
	//ofs.imbue(std::locale("Japanese", LC_COLLATE));
	//ofs.imbue(std::locale("Japanese", LC_CTYPE));
	ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
	ofs.open(path, std::ios::app);
	ofs << _get_timestamp() << " [TRACE] " << something.c_str() << std::endl;
	ofs.close();
}

logger::logger(const std::wstringstream& something)
{
	const _TCHAR* path = _T("myapp.log");
	std::wofstream ofs;
	//ofs.imbue(std::locale("Japanese", LC_COLLATE));
	//ofs.imbue(std::locale("Japanese", LC_CTYPE));
	ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
	ofs.open(path, std::ios::app);
	ofs << _get_timestamp() << " [TRACE] " << something.str() << std::endl;
	ofs.close();
}

logger::~logger()
{

}
