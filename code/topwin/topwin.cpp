#include <stdio.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <string>
#include <tchar.h>
#include <locale.h>

std::wstring get_current_timestamp()
{
    SYSTEMTIME s;
    GetLocalTime(&s);
    _TCHAR buffer[30] = _T("");
    wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
        s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
    return buffer;
}

std::wstring GetLastErrorText(DWORD error)
{
    std::wstring text;
    TCHAR buffer[1000] = _T("");
    wsprintf(buffer, _T("0x%08X"), error);
    text.append(buffer);
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, buffer, sizeof(buffer), NULL);
    text.append(_T(":"));
    text.append(buffer);
    return text;
}

std::wstring get_window_text(HWND hwnd)
{
    wchar_t title[1024] = _T("");
    if (!GetWindowText(hwnd, title, sizeof(title) / sizeof(wchar_t))) {
        const DWORD error = GetLastError();
        const std::wstring error_text = GetLastErrorText(error);
        return error_text;
    }
    return title;
}

void diagnose()
{
    // 最前面のウィンドウハンドル
    HWND hwnd = GetForegroundWindow();
    wchar_t buffer[1024] = _T("");
    wsprintf(buffer, _T("0x%08X"), hwnd);

    // ウィンドウのテキスト
    std::wstring title = get_window_text(hwnd);

    // 出力
    std::wstringstream text;
    text << get_current_timestamp() << _T(" [TRACE] HWND: ") << buffer << _T(", TITLE: ") << title;
    std::wcout << text.str() << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Japanese");
    _wsetlocale(LC_ALL, _T("Japanese"));

    while (true)
    {
        diagnose();
        Sleep(500);
    }
}
