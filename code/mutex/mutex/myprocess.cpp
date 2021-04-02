#include "myprocess.h"
#include "..\common\util.h"
#include "..\common\mutex.h"

process::process(const _TCHAR* path)
{
	memset(&this->startup_info, 0x00, sizeof(this->startup_info));
	memset(&this->process_info, 0x00, sizeof(this->process_info));

	string command = path;
	const BOOL result = CreateProcess(NULL, (_TCHAR*)command.c_str(), NULL, FALSE,
		0, NULL, NULL, NULL, &this->startup_info, &this->process_info);
	if (!result)
	{
		_trace(_T("CreateProcess() failed."));
		report_error();
		return;
	}

	{
		std::wstringstream line;
		line << _T("プロセスを起動しました。(pid: ") << this->process_info.dwProcessId << _T(")");
		_trace(line);
	}
}

void process::join()
{
	if (this->process_info.hProcess != NULL)
	{
		{
			std::wstringstream line;
			line << _T("プロセス終了を待機しています... (pid: ") << this->process_info.dwProcessId << _T(")");
			_trace(line);
		}
		{
			const auto result = WaitForSingleObject(this->process_info.hProcess, INFINITE);
			const DWORD exitCode = getExitCodeOfProcess(this->process_info.hProcess);
			std::wstringstream line;
			line << _T("プロセスはコード ") << exitCode << _T(" で終了しました。");
			_trace(line);
		}
		CloseHandle(this->process_info.hProcess);
		// report_error();
		this->process_info.hProcess = NULL;
	}
	if (this->process_info.hThread != NULL)
	{
		CloseHandle(this->process_info.hThread);
		// report_error();
		this->process_info.hThread = NULL;
	}
}

process::~process()
{
	this->join();
}
