// 日本語 UTF-8 with BOM
#pragma once


#include <Windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "string.h"

// 最後に発生した Win32 エラーの文字列表現を返します。
string get_last_error_text();
// 最後に発生した Win32 エラーの文字列表現を返します。
// @params `error` GetLastError() の戻り値
string get_last_error_text(DWORD error);
string get_date_string0();
string get_current_timestamp();
string get_process_id();
string get_thread_id();

void write_log(const _TCHAR* level, const _TCHAR* s);

void log_trace(const _TCHAR* s);
void log_trace(const string& s);
void log_trace(const stringstream& s);

void log_debug(const _TCHAR* s);
void log_debug(const string& s);
void log_debug(const stringstream& s);

void log_info(const _TCHAR* s);
void log_info(const string& s);
void log_info(const stringstream& s);

void log_warn(const _TCHAR* s);
void log_warn(const string& s);
void log_warn(const stringstream& s);

void log_error(const _TCHAR* s);
void log_error(const string& s);
void log_error(const stringstream& s);

void report_error();

void rtrim(wchar_t* s);
void rtrim(char* s);

// プロセスの終了ステータスを返します。
// @param `handle` プロセスのハンドル
DWORD get_exitcode_of_process(const HANDLE& handle);
