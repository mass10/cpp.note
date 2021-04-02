// UTF-8 with BOM

#include "pch.h"
#include "util.h"
#include "string.h"
#include "mutex.h"
#include <Windows.h>
#include <tchar.h>
#include <fstream>
#include <codecvt>

void rtrim(wchar_t* s)
{
	if (s[0] == 0x00) return;

	while (*s)
		s++;

	for (; ; s--)
	{
		const wchar_t c = *s;
		if (c == ' ')
			*s = 0x00;
		else if (c == 0x00)
			*s = 0x00;
		else if (c == '\t')
			*s = 0x00;
		else if (c == '\r')
			*s = 0x00;
		else if (c == '\n')
			*s = 0x00;
		else
			break;
	}
}

void rtrim(char* s)
{
	if (s[0] == 0x00) return;

	while (*s)
		s++;

	for (; ; s--)
	{
		const char c = *s;
		if (c == ' ')
			*s = 0x00;
		else if (c == 0x00)
			*s = 0x00;
		else if (c == '\t')
			*s = 0x00;
		else if (c == '\r')
			*s = 0x00;
		else if (c == '\n')
			*s = 0x00;
		else
			break;
	}
}

string GetLastErrorText()
{
	return GetLastErrorText(GetLastError());
}

string GetLastErrorText(DWORD error)
{
	_TCHAR buffer[1000] = _T("");
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, buffer, sizeof(buffer) / sizeof(_TCHAR), NULL);
	rtrim(buffer);
	return buffer;
}

SYSTEMTIME get_local_time()
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	return s;
}

string get_date_string0()
{
	const SYSTEMTIME s = get_local_time();
	_TCHAR buffer[99] = _T("");
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR),
		_T("%04d%02d%02d"), s.wYear, s.wMonth, s.wDay);
	return buffer;
}

string GetCurrentTimestamp()
{
	const SYSTEMTIME s = get_local_time();
	_TCHAR buffer[99] = _T("");
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR),
		_T("%04u-%02u-%02u %02u:%02u:%02u.%03u"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

void report_error()
{
	// ※※※ ロギングの排他ロック ※※※
	mymutex lock;
	const DWORD error = GetLastError();
	if (error == 0)
		return;
	auto timestamp = get_current_timestamp();
	string message_text = GetLastErrorText(error);
	const DWORD process_id = GetCurrentProcessId();
	_tprintf(_T("%s [FATAL] [process %d] 予期しないエラーです。 理由: %s(%d)\n"), timestamp.c_str(), process_id, message_text.c_str(), error);
	fflush(stdout);
}

string get_current_timestamp()
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR buffer[99] = _T("");
	wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

void _trace(const _TCHAR* message) {

	// ※※※ ロギングの排他ロック ※※※
	mymutex lock;
	const DWORD process_id = GetCurrentProcessId();
	_tprintf(_T("%s [TRACE] [process %d] %s\n"), get_current_timestamp().c_str(), process_id, message);
	fflush(stdout);
}

void _trace(const std::wstring& message) {

	_trace(message.c_str());
}

void _trace(const std::wstringstream& message) {

	_trace(message.str());
}
