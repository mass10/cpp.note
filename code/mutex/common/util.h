// 日本語 UTF-8 with BOM
#pragma once


#include <Windows.h>
#include <tchar.h>
#include "string.h"

string GetLastErrorText();
string GetLastErrorText(DWORD error);
string get_date_string0();
string GetCurrentTimestamp();
string _get_process_id();
string _get_thread_id();

/*
void _write_log(const _TCHAR* level, const _TCHAR* s);
void _trace(const _TCHAR* s);
void _trace(const string& s);
void _trace(const stringstream& s);
void _info(const _TCHAR* s);
void _info(const string& s);
void _info(const stringstream& s);
void _debug(const _TCHAR* s);
void _debug(const string& s);
void _debug(const stringstream& s);
void _warn(const _TCHAR* s);
void _warn(const string& s);
void _warn(const stringstream& s);
void _error(const _TCHAR* s);
void _error(const string& s);
void _error(const stringstream& s);
*/

void report_error();
void rtrim(wchar_t* s);
void rtrim(char* s);

string get_current_timestamp();
