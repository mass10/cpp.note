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
		log_trace(_T("CreateProcess() failed."));
		report_error();
		return;
	}

	{
		std::wstringstream line;
		line << _T("プロセスを起動しました。(pid: ") << this->process_info.dwProcessId << _T(")");
		log_trace(line);
	}
}

void process::join()
{
	if (this->process_info.hProcess != NULL)
	{
		{
			std::wstringstream line;
			line << _T("プロセス終了を待機しています... (pid: ") << this->process_info.dwProcessId << _T(")");
			log_trace(line);
			report_error();
		}
		{
			// SetLastError(0);
			const auto result = WaitForSingleObject(this->process_info.hProcess, INFINITE);
			report_error();

			const DWORD exitCode = get_exitcode_of_process(this->process_info.hProcess);
			std::wstringstream line;
			line << _T("プロセスはコード ") << exitCode << _T(" で終了しました。");
			log_trace(line);
		}

		SetLastError(0);
		CloseHandle(this->process_info.hProcess);
		report_error();

		this->process_info.hProcess = NULL;
	}

	if (this->process_info.hThread != NULL)
	{
		SetLastError(0);
		CloseHandle(this->process_info.hThread);
		report_error();

		this->process_info.hThread = NULL;
	}
}

process::~process()
{
	this->join();
}
