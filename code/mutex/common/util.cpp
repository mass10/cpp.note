// UTF-8 with BOM

#include "pch.h"
#include "util.h"
#include "string.h"
#include "mutex.h"
#include <Windows.h>
#include <tchar.h>
#include <fstream>
#include <codecvt>

void rtrim(wchar_t* s) {

	if (s == NULL) return;
	if (s[0] == 0x00) return;

	while (*s)
		s++;

	for (; ; s--) {
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

void rtrim(char* s) {

	if (s == NULL) return;
	if (s[0] == 0x00) return;

	while (*s)
		s++;

	for (; ; s--) {
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

string get_last_error_text() {

	return get_last_error_text(GetLastError());
}

string get_last_error_text(DWORD error) {

	_TCHAR buffer[1000] = _T("");
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, buffer, sizeof(buffer) / sizeof(_TCHAR), NULL);
	rtrim(buffer);
	return buffer;
}

SYSTEMTIME get_local_time() {

	SYSTEMTIME s;
	GetLocalTime(&s);
	return s;
}

string get_date_string0() {

	const SYSTEMTIME s = get_local_time();
	_TCHAR buffer[99] = _T("");
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR),
		_T("%04d%02d%02d"), s.wYear, s.wMonth, s.wDay);
	return buffer;
}

void report_error() {

	const DWORD error = GetLastError();
	if (error == 0)
		return;

	string message_text = get_last_error_text(error);
	stringstream line;
	line << _T("予期しないエラーです。理由: ") << message_text.c_str() << _T(" (") << error << _T(")");
	log_error(line);
}

string get_current_timestamp() {

	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR buffer[99] = _T("");
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR),
		_T("%04u-%02u-%02u %02u:%02u:%02u.%03u"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

string format_pid() {
	_TCHAR buffer[99];
	const DWORD process_id = GetCurrentProcessId();
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR), _T("0x%08X"), process_id);
	return buffer;
}

void log_trace(const _TCHAR* message) {

	// ※※※ ロギングの排他ロック ※※※
	mymutex lock;

	const auto process_id = format_pid();
	_tprintf(_T("%s [TRACE] [process %s] %s\n"), get_current_timestamp().c_str(), process_id.c_str(), message);
	fflush(stdout);
}

void log_trace(const string& message) {

	log_trace(message.c_str());
}

void log_trace(const stringstream& message) {

	log_trace(message.str());
}

void log_error(const _TCHAR* message) {

	// ※※※ ロギングの排他ロック ※※※
	mymutex lock;

	const auto process_id = format_pid();
	_tprintf(_T("%s [ERROR] [process %s] %s\n"), get_current_timestamp().c_str(), process_id.c_str(), message);
	fflush(stdout);
}

void log_error(const string& message) {

	log_error(message.c_str());
}

void log_error(const stringstream& message) {

	log_error(message.str());
}

DWORD get_exitcode_of_process(const HANDLE& handle) {

	DWORD exitCode = 0;
	GetExitCodeProcess(handle, &exitCode);
	return exitCode;
}
