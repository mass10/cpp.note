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
		report_error();
		return;
	}

	mymutex lock;
	_tprintf(_T("プロセスを起動しました。(pid: %d)\n"), this->process_info.dwProcessId);
}

void process::join()
{
	if (this->process_info.hProcess != NULL)
	{
		{
			mymutex lock;
			_tprintf(_T("プロセス終了を待機しています... (pid: %d)\n"), this->process_info.dwProcessId);
		}
		WaitForSingleObject(this->process_info.hProcess, INFINITE);
		report_error();
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

process::~process()
{
	this->join();
}
