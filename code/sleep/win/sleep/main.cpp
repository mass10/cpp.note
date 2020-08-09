#include <Windows.h>
#include <signal.h>
#include <tchar.h>
#include <string>
#include <sstream>

volatile bool _quit = false;

std::wstring get_current_timestamp()
{
    SYSTEMTIME s;
    GetLocalTime(&s);
    _TCHAR buffer[40];
    _stprintf_s(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
        s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
    return buffer;
}

#define __TRACE(x) { std::wstringstream line; line << get_current_timestamp() << _T(" [trace] ") << x; _tprintf(_T("%s\n"), line.str().c_str()); }

void on_signal(int signal)
{
    __TRACE(_T(" Caught signal ") << signal << _T("."));
    _quit = true;
}

int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale(LC_ALL, _T("Japanese"));

    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);

    __TRACE(_T("### START ###"));

    while (!_quit)
    {
        __TRACE(_T("(waiting)"));

        // signal によって割り込みが派生しても、Sleep は制御を返さず、待機します。
        Sleep(3 * 1000);
    }

    __TRACE(_T("--- END ---"));

    return 0;
}
