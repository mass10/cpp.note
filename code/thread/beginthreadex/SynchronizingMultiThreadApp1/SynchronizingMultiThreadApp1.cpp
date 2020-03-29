// SynchronizingMultiThreadApp1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <process.h>
#include <fstream>
#include <sstream>
#include <clocale>
#include <codecvt>

class crit
{
public:
	crit();
	~crit();
	static void init();
	static void free();
private:
	static CRITICAL_SECTION _section;
};

CRITICAL_SECTION crit::_section;

void crit::init()
{
	memset(&_section, 0x00, sizeof(_section));
	InitializeCriticalSection(&_section);
}

void crit::free()
{
	DeleteCriticalSection(&_section);
}

crit::crit()
{
	EnterCriticalSection(&_section);
}

crit::~crit()
{
	LeaveCriticalSection(&_section);
}

std::wstring get_current_timestamp()
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR buffer[99] = _T("");
	wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"), s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

void _trace(const _TCHAR* s)
{
	crit c;

	// プロセスID
	const DWORD processs_id = GetCurrentProcessId();
	char process_id_buffer[32] = "";
	sprintf_s(process_id_buffer, "%08x", processs_id);

	// スレッドID
	const DWORD thread_id = GetCurrentThreadId();
	char thread_id_buffer[32] = "";
	sprintf_s(thread_id_buffer, "%08x", thread_id);

	// timestamp
	const std::wstring timestamp = get_current_timestamp();

	// ファイル
	{
		std::wofstream ofs(_T("application.log"), std::ios::app);
		auto enc1 = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [TRACE] ") << s << std::endl;
		ofs.close();
	}

	// 標準出力
	{
		auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		//auto enc2 = std::wcout.imbue(std::locale("Japanese"));
		std::wcout << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [TRACE] ") << s << std::endl;
	}
}

void _error(const _TCHAR* s)
{
	crit c;

	// プロセスID
	const DWORD processs_id = GetCurrentProcessId();
	char process_id_buffer[32] = "";
	sprintf_s(process_id_buffer, "%08x", processs_id);

	// スレッドID
	const DWORD thread_id = GetCurrentThreadId();
	char thread_id_buffer[32] = "";
	sprintf_s(thread_id_buffer, "%08x", thread_id);

	// timestamp
	const std::wstring timestamp = get_current_timestamp();

	// ファイル
	{
		std::wofstream ofs(_T("application.log"), std::ios::app);
		auto enc1 = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [ERROR] ") << s << std::endl;
		ofs.close();
	}

	// 標準出力
	{
		auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		// auto enc2 = std::wcout.imbue(std::locale("Japanese"));
		std::wcout << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [ERROR] ") << s << std::endl;
	}
}

void _trace(const std::wstring& s)
{
	_trace(s.c_str());
}

void _trace(const std::wstringstream& s)
{
	_trace(s.str());
}

enum class thread_state
{
	ready,
	running,
	closing
};

class thread
{
public:
	thread();
	~thread();
	void run();
	void wait();
	void cancel();
	bool alive() const;
private:
	static unsigned __stdcall thread_func(void* thread_param);
	void main();
	std::wstring get_request() const;
	unsigned int _thread_id;
	volatile thread_state _state;
	std::wstring _request;
	HANDLE _thread_handle;
};

thread::thread()
{
	this->_thread_id = 0;
	this->_thread_handle = NULL;
	this->_state = thread_state::ready;
}

thread::~thread()
{
	if (this->_thread_handle == NULL)
		return;
	CloseHandle(this->_thread_handle);
	this->_thread_handle = NULL;
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
	_trace(_T("<thread_func()> $$$ start $$$"));
	unsigned int i = 0;
	while (this->alive())
	{
		if (10 <= i)
			break;
		Sleep(100);
		//_trace(_T("<thread::wait()> (処理中)"));
		i++;
	}
	this->_state == thread_state::closing;
	_trace(_T("<thread_func()> --- end ---"));
}

void thread::wait()
{
	if (this->_thread_handle == NULL)
		return;
	_trace(_T("<thread::wait()> スレッドの終了を待っています..."));
	WaitForSingleObject(this->_thread_handle, INFINITE);
	_trace(_T("<thread::wait()> スレッドの終了を待っています... [OK]"));
	CloseHandle(this->_thread_handle);
	this->_thread_handle = NULL;
}

void thread::run()
{
	this->wait();
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &thread_func, (void*)this, 0, &this->_thread_id);
	if (handle == NULL) {
		_error(_T("<thread::run()> Cannot create a new thread..."));
		return;
	}
	while (this->_state == thread_state::ready) {
		_trace(_T("<thread::run()> Waiting for a new thread ready..."));
		Sleep(1);
	}
	_trace(_T("<thread::run()> Created a new thread!"));
	this->_thread_handle = handle;
}

class application
{
public:
	application();
	~application();
	void run();
private:
};

application::application()
{
	crit::init();
}

application::~application()
{
	crit::free();
}

void application::run()
{
	_trace(_T("<main()> ### start ###"));

	thread t1;
	thread t2;
	thread t3;

	t1.run();
	t2.run();
	t3.run();

	t1.wait();
	t2.wait();
	t3.wait();

	_trace(_T("<main()> --- end ---"));
}

int main()
{
	application app;
	app.run();
}
