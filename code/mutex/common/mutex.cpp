#include "pch.h"
#include "mutex.h"
#include "string.h"
#include "util.h"

HANDLE create_mutex(const _TCHAR* mutex_name) {

	HANDLE handle = CreateMutex(
		NULL /* security attributes */,
		FALSE /* not as initial owner */,
		mutex_name /* its name */);

	const DWORD error = GetLastError();
	if (handle == NULL) {
		const string message = get_last_error_text(error);
		_tprintf(_T("[FATAL] CreateMutex failed. reason: %s (%d)\n"), message.c_str(), error);
		fflush(stdout);
		exit(0);
	}

	if (error == ERROR_ALREADY_EXISTS)
		// success
		SetLastError(0);

	return handle;
}

mymutex::mymutex() :
	_handle(NULL)
{
	while (true) {
		this->_handle = create_mutex(_T("app1 の mutex 2"));
		if (this->_handle == NULL) {
			Sleep(5);
			continue;
		}
		WaitForSingleObject(this->_handle, INFINITE);
		break;
	}
}

mymutex::~mymutex() {
	if (this->_handle == NULL)
		return;
	if (this->_handle == INVALID_HANDLE_VALUE)
		return;
	ReleaseMutex(this->_handle);
	CloseHandle(this->_handle);
}
