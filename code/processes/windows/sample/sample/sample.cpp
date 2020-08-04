// sample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <windows.h>
#include <tchar.h>
#include <string>
#include <locale.h>

#ifdef UNICODE
typedef std::wstring string;
#else
typedef std::string string;
#endif

void rtrim(_TCHAR* line)
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

string getLastErrorMessage(DWORD error)
{
    _TCHAR messageBuffer[2048] = _T("");
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error,
        LANG_USER_DEFAULT, messageBuffer, sizeof(messageBuffer) / sizeof(_TCHAR), NULL);
    rtrim(messageBuffer);
    return messageBuffer;
}

void report_error()
{
    const DWORD error = GetLastError();
    if (error == 0)
        return;
    const string message = getLastErrorMessage(error);
    _tprintf(_T("[ERROR] %s(error: %d)\n"), message.c_str(), error);
}


class process
{
public:
    process();
    ~process();
    bool run();
private:
    STARTUPINFO startup_info = {};
    PROCESS_INFORMATION process_info = {};
};

process::process()
{
}

bool process::run()
{
    CreateProcess(_T("C:\\Windows\\notepad.exe"), NULL, NULL,
        FALSE, NULL, NULL, NULL, _T("C:\\Windows"), &startup_info, &process_info);
    if (process_info.hProcess == NULL)
    {
        report_error();
        return false;
    }
    return true;
}

process::~process()
{
    // 終了を待機
    if (process_info.hProcess != NULL)
    {
        WaitForSingleObject(process_info.hProcess, INFINITE);
        report_error();
    }

    if (this->process_info.hProcess != NULL)
    {
        CloseHandle(this->process_info.hProcess);
        report_error();
        this->process_info.hProcess = NULL;
    }

    if (this->process_info.hThread != NULL)
    {
        CloseHandle(this->process_info.hThread);
        report_error();
        this->process_info.hThread = NULL;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    UNREFERENCED_PARAMETER(argc);

    _tsetlocale(LC_ALL, TEXT("Japanese"));

    process p;
    p.run();
}
