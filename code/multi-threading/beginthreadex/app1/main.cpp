#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <process.h>
#include <crtdbg.h>

#include <fstream>
#include <sstream>
#include <clocale>
#include <codecvt>
#include <map>
#include <string>



#ifdef UNICODE
typedef std::wstring string;
typedef std::wstringstream stringstream;
#else
typedef std::string string;
typedef std::stringstream stringstream;
#endif


///////////////////////////////////////////////////////////////////////////////
// 各種汎用操作

string get_current_timestamp() {
	SYSTEMTIME s;
	GetLocalTime(&s);
	_TCHAR buffer[99] = _T("");
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR), _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////
class critical_section_lifetime {
	friend class application;
private:
	critical_section_lifetime();
	~critical_section_lifetime();
};

class critical_section {
	friend class critical_section_lifetime;
public:
	critical_section();
	~critical_section();
private:
	static void init();
	static void free();
	static CRITICAL_SECTION _section;
};

CRITICAL_SECTION critical_section::_section;

critical_section_lifetime::critical_section_lifetime() {
	critical_section::init();
}

critical_section_lifetime::~critical_section_lifetime() {
	critical_section::free();
}

void critical_section::init() {
	memset(&_section, 0x00, sizeof(_section));
	InitializeCriticalSection(&_section);
}

void critical_section::free() {
	DeleteCriticalSection(&_section);
}

critical_section::critical_section() {
	EnterCriticalSection(&_section);
}

critical_section::~critical_section() {
	LeaveCriticalSection(&_section);
}

///////////////////////////////////////////////////////////////////////////////
// ロギング

class logger {
public:
	static void trace(const _TCHAR* s);
	static void trace(const string& s);
	static void trace(const stringstream& s);
	static void error(const _TCHAR* s);
	static void error(const string& s);
	static void error(const stringstream& s);
};

void _trace(const _TCHAR* level, const _TCHAR* s) {
	critical_section c;

	// プロセスID
	const DWORD processs_id = GetCurrentProcessId();
	_TCHAR process_id_buffer[9] = _T("");
	_stprintf_s(process_id_buffer, sizeof(process_id_buffer) / sizeof(_TCHAR), _T("%08x"), processs_id);

	// スレッドID
	const DWORD thread_id = GetCurrentThreadId();
	_TCHAR thread_id_buffer[9] = _T("");
	_stprintf_s(thread_id_buffer, sizeof(thread_id_buffer) / sizeof(_TCHAR), _T("%08x"), thread_id);

	// timestamp
	const string timestamp = get_current_timestamp();

	stringstream line;
	line << timestamp.c_str() << _T(" (process: ") << process_id_buffer << _T(", thread: ") << thread_id_buffer << _T(")") << _T(" [") << level << _T("] ") << s << std::endl;

	// ファイル
	{
		std::wofstream ofs(_T("application.log"), std::ios::app);
		auto enc1 = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << line.str();
		ofs.close();
	}

	// 標準出力
	{
		_tprintf(line.str().c_str());
	}
}

void logger::trace(const _TCHAR* s) {
	_trace(_T("TRACE"), s);
}

void logger::error(const _TCHAR* s) {
	_trace(_T("ERROR"), s);
}

void logger::trace(const std::wstring& s) {
	_trace(_T("TRACE"), s.c_str());
}

void logger::trace(const std::wstringstream& s) {
	_trace(_T("TRACE"), s.str().c_str());
}

///////////////////////////////////////////////////////////////////////////////
// スレッド操作

enum class thread_state {
	ready,
	running,
	closing
};

class thread {
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

thread::thread() {
	this->_thread_id = 0;
	this->_thread_handle = NULL;
	this->_state = thread_state::ready;
}

thread::~thread() {
	if (this->_thread_handle == NULL)
		return;
	CloseHandle(this->_thread_handle);
	this->_thread_handle = NULL;
}

bool thread::alive() const {
	return this->_request == _T("");
}

void thread::cancel() {
	this->_request = _T("cancel");
}

std::wstring thread::get_request() const {
	return this->_request;
}

unsigned __stdcall thread::thread_func(void* thread_param) {
	thread* pthis = (thread*)thread_param;
	pthis->main();
	_endthreadex(0);
	return 0;
}

void thread::main() {
	this->_state = thread_state::running;
	logger::trace(_T("<thread_func()> $$$ start $$$"));
	unsigned int i = 0;
	while (this->alive()) {
		if (10 <= i)
			break;
		Sleep(100);
		//logger::trace(_T("<thread::wait()> (処理中)"));
		i++;
	}
	this->_state = thread_state::closing;
	logger::trace(_T("<thread_func()> --- end ---"));
}

void thread::wait() {
	if (this->_thread_handle == NULL)
		return;
	logger::trace(_T("<thread::wait()> スレッドの終了を待っています..."));
	WaitForSingleObject(this->_thread_handle, INFINITE);
	logger::trace(_T("<thread::wait()> スレッドの終了を待っています... [OK]"));
	CloseHandle(this->_thread_handle);
	this->_thread_handle = NULL;
}

void thread::run() {
	this->wait();
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &thread_func, (void*)this, 0, &this->_thread_id);
	if (handle == NULL) {
		logger::error(_T("<thread::run()> Cannot create a new thread..."));
		return;
	}
	WaitForSingleObject(handle, INFINITE);
	while (this->_state == thread_state::ready) {
		logger::trace(_T("<thread::run()> Waiting for a new thread ready..."));
		Sleep(1);
	}
	logger::trace(_T("<thread::run()> Created a new thread!"));
	this->_thread_handle = handle;
}

///////////////////////////////////////////////////////////////////////////////
// アプリケーション本体

class application {
public:
	application();
	~application();
	void run();
private:
	critical_section_lifetime _critical_section_lifetime;
};

application::application() {
}

application::~application() {
}

void application::run() {

	logger::trace(_T("<main()> ### start ###"));

	thread t1;
	thread t2;
	thread t3;

	t1.run();
	t2.run();
	t3.run();

	t1.wait();
	t2.wait();
	t3.wait();

	logger::trace(_T("<main()> --- end ---"));
}

///////////////////////////////////////////////////////////////////////////////
// エントリーポイント

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_tsetlocale(LC_ALL, _T("Japanese"));

	application app;
	app.run();
}
