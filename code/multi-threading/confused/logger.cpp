#include "logger.h"
#include "critical_section.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <clocale>
#include <codecvt>

std::wstring get_current_timestamp()
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR buffer[99] = _T("");
	wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"), s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

void logger::trace(const _TCHAR* s)
{
	// クリティカルセクションを使用しない例
	if (false) critical_section c;

	// プロセスID
	const DWORD processs_id = GetCurrentProcessId();
	char process_id_buffer[32] = "";
	sprintf_s(process_id_buffer, "%08x", processs_id);

	// スレッドID
	const DWORD thread_id = GetCurrentThreadId();
	char thread_id_buffer[32] = "";
	sprintf_s(thread_id_buffer, "%08x", thread_id);

	// timestamp
	const std::wstring timestamp = get_current_timestamp();

	// ファイル
	{
		std::wofstream ofs(_T("cunfused.log"), std::ios::app);
		auto enc1 = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [TRACE] ") << s << std::endl;
		ofs.close();
	}

	// 標準出力
	{
		auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		//auto enc2 = std::wcout.imbue(std::locale("Japanese"));
		std::wcout << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [TRACE] ") << s << std::endl;
	}
}

void logger::error(const _TCHAR* s)
{
	if (false) critical_section c;
	
	// プロセスID
	const DWORD processs_id = GetCurrentProcessId();
	char process_id_buffer[32] = "";
	sprintf_s(process_id_buffer, "%08x", processs_id);

	// スレッドID
	const DWORD thread_id = GetCurrentThreadId();
	char thread_id_buffer[32] = "";
	sprintf_s(thread_id_buffer, "%08x", thread_id);

	// timestamp
	const std::wstring timestamp = get_current_timestamp();

	// ファイル
	{
		std::wofstream ofs(_T("cunfused.log"), std::ios::app);
		auto enc1 = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [ERROR] ") << s << std::endl;
		ofs.close();
	}

	// 標準出力
	{
		auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		// auto enc2 = std::wcout.imbue(std::locale("Japanese"));
		std::wcout << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [ERROR] ") << s << std::endl;
	}
}

void logger::trace(const std::wstring& s)
{
	trace(s.c_str());
}

void logger::trace(const std::wstringstream& s)
{
	trace(s.str());
}
