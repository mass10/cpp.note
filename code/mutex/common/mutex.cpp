#include "pch.h"
#include "mutex.h"
#include "string.h"
#include "util.h"

HANDLE create_mutex() {

	//SECURITY_DESCRIPTOR sd;
	//InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	//SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE);

	//SECURITY_ATTRIBUTES secAttribute;
	//secAttribute.nLength = sizeof(secAttribute);
	//secAttribute.lpSecurityDescriptor = &sd;
	//secAttribute.bInheritHandle = TRUE;

	HANDLE handle = CreateMutex(NULL, FALSE, _T("app1 の mutex 2"));
	const DWORD error = GetLastError();
	if (handle == NULL)
	{
		const string message = GetLastErrorText(error);
		_tprintf(_T("[FATAL] CreateMutex failed. reason: %s (%d)\n"), message.c_str(), error);
		fflush(stdout);
		exit(0);
	}
	return handle;
}

mymutex::mymutex() :
	_handle(NULL)
{
	while (true) {
		this->_handle = create_mutex();
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
