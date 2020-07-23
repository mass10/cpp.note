#include "thread.h"
#include "logger.h"
#include <Windows.h>
#include <process.h>

void _close_handle(HANDLE& handle)
{
	if (handle == NULL)
		return;
	CloseHandle(handle);
	handle = NULL;
}

thread::thread()
{
	this->_thread_id = 0;
	this->_thread_handle = NULL;
	this->_state = thread_state::ready;
}

thread::~thread()
{
	_close_handle(this->_thread_handle);
}

bool thread::alive() const
{
	return this->_request == _T("");
}

void thread::cancel()
{
	this->_request = _T("cancel");
}

std::wstring thread::get_request() const
{
	return this->_request;
}

unsigned __stdcall thread::thread_func(void* thread_param)
{
	thread* pthis = (thread*)thread_param;
	pthis->main();
	_endthreadex(0);
	return 0;
}

void thread::main()
{
	this->_state = thread_state::running;
	logger::trace(_T("<thread_func()> $$$ start $$$"));
	for (unsigned int i = 0; i < 1000; i++)
	{
		if (!this->alive())
			break;
		if (100 <= i)
			break;
		// Sleep(1);
		logger::trace(_T("<thread::wait()> (処理中)"));
		i++;
	}
	this->_state = thread_state::closing;
	logger::trace(_T("<thread_func()> --- end ---"));
}

void thread::wait()
{
	if (this->_thread_handle == NULL)
		return;
	logger::trace(_T("<thread::wait()> スレッドの終了を待っています..."));
	WaitForSingleObject(this->_thread_handle, INFINITE);
	logger::trace(_T("<thread::wait()> スレッドの終了を待っています... [OK]"));
	_close_handle(this->_thread_handle);
}

void thread::run()
{
	this->wait();
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &thread_func, (void*)this, 0, &this->_thread_id);
	if (handle == NULL) {
		logger::error(_T("<thread::run()> Cannot create a new thread..."));
		return;
	}
	while (this->get_current_state() == thread_state::ready) {
		logger::trace(_T("<thread::run()> Waiting for a new thread ready..."));
		Sleep(1);
	}
	logger::trace(_T("<thread::run()> Created a new thread!"));
	this->_thread_handle = handle;
}

thread_state thread::get_current_state() const
{
	return this->_state;
}
