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
			_trace(_T("try WaitForSingleObject"));
			const auto result = WaitForSingleObject(this->process_info.hProcess, INFINITE);
			if (result == WAIT_OBJECT_0)
			{
				_trace(_T("WAIT_OBJECT_0"));
				DWORD exitCode = 0;
				GetExitCodeProcess(this->process_info.hProcess, &exitCode);
				std::wstringstream line;
				line << _T("プロセスはコード ") << exitCode << _T(" で終了しました。");
				_trace(line);
			}
			else if (result == WAIT_ABANDONED)
			{
				_trace(_T("WAIT_ABANDONED"));
			}
			else
			{
				_trace(_T("プロセスの待機に失敗しました。後続のエラーを確認してください。"));
				report_error();
			}
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
