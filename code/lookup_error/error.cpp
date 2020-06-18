#include <Windows.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <iostream>

std::wstring get_last_error_message(int error)
{
    LPVOID buffer = NULL;
    const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    DWORD result = FormatMessage(flags, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, NULL);
    if (buffer == NULL)
        return L"";
    std::wstring message = (const wchar_t*)buffer;
    LocalFree(buffer);
    return message;
}

void lookup(int error)
{
    std::wstring message = get_last_error_message(error);
    if (message == L"")
        return;
    wprintf(L"%d: %s\n", error, message.c_str());
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Japanese");
    _wsetlocale(LC_ALL, L"Japanese");
    if (argc <= 1) {
        return 0;
    }
    lookup(atoi(argv[1]));
    return 0;
}
