//
// ウィンドウを列挙するアプリケーションです。
//

#include <crtdbg.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <codecvt>

//void _trace(const std::wstringstream line)
//{
//	// プロセスID
//	const std::wstring process_id_buffer = _get_process_id();
//	// スレッドID
//	const std::wstring thread_id_buffer = _get_thread_id();
//	// timestamp
//	const std::wstring timestamp = GetCurrentTimestamp();
//
//}

std::wstring dword2hex(void* address)
{
	_TCHAR buffer[32];
	wsprintf(buffer, L"0x%08X", address);
	return buffer;
}

std::wstring dword2hex(DWORD value)
{
	_TCHAR buffer[32];
	wsprintf(buffer, L"0x%08X", value);
	return buffer;
}

std::wstring get_current_timestamp()
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR buffer[99] = _T("");
	wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

void _rtrim(_TCHAR* line)
{
	_TCHAR* pos = line;

	while (*pos != 0x00)
		pos++;

	while (line <= pos)
	{
		switch (*pos)
		{
		case 0x00:
			break;
		case L' ':
		case L'\t':
		case L'\r':
		case L'\n':
			*pos = 0x00;
			break;
		default:
			// 何かの文字を検出
			return;
		}
		pos--;
	}
}

std::wstring get_last_error_message(DWORD error)
{
	_TCHAR message_buffer[1000] = L"";
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, message_buffer, sizeof(message_buffer) / sizeof(_TCHAR), NULL);
	_rtrim(message_buffer);
	return message_buffer;
}

std::wstring get_last_error_message()
{
	return get_last_error_message(GetLastError());
}

std::wstring get_window_text(HWND hWnd)
{
	_TCHAR buffer[4000] = L"";
	GetWindowText(hWnd, buffer, sizeof(buffer) / sizeof(_TCHAR));
	return buffer;
}

int _indent = 0;

std::wstring get_window_class(HWND hWnd)
{
	_TCHAR buffer[4000] = L"";
	GetClassName(hWnd, buffer, sizeof(buffer) / sizeof(_TCHAR));
	return buffer;
}

BOOL CALLBACK enum_window_proc(HWND hwnd, LPARAM lParam)
{
	// ウィンドウのタイトル
	const std::wstring title = get_window_text(hwnd);

	// ウィンドウクラス名
	const std::wstring class_name = get_window_class(hwnd);

	// ウィンドウのプロセスID
	DWORD window_process_id = 0;
	const DWORD window_thread_id = GetWindowThreadProcessId(hwnd, &window_process_id);

	{
		std::wstringstream line;
		for (int i = 0; i < _indent; i++)
		{
			line << L"    ";
		}
		line << L"+"
			<< L" HWND: [" << dword2hex(hwnd) << L"]"
			<< L", PID: [" << dword2hex(window_process_id) << L"]"
			<< L", TEXT: [" << title << L"]"
			<< L", WINDOW_CLASS: [" << class_name << L"]"
			<< L", THREAD ID: [" << dword2hex(window_thread_id) << L"]";
		wprintf(_T("%s\n"), line.str().c_str());
	}

	// さらに子ウィンドウを探索...
	_indent++;

	if (!EnumChildWindows(hwnd, enum_window_proc, NULL))
	{
		const DWORD error = GetLastError();
		if (error != 0)
		{
			const std::wstring message = get_last_error_message(error);
			std::wstringstream line;
			line << L"[ERROR] ERROR: [" << error << L"], DETAIL: [" << message << L"]";
			wprintf(L"%s\n", line.str().c_str());
		}
	}

	_indent--;

	return TRUE;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	setlocale(LC_ALL, "Japanese");
	_tsetlocale(LC_ALL, L"Japanese");
	
	LPARAM lparam = 0;
	EnumWindows(&enum_window_proc, lparam);
}
