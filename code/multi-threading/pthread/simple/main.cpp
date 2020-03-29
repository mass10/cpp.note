#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <wchar.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <clocale>
#include <codecvt>


pthread_mutex_t _mutex;

class mutex {
public:
	mutex();
	~mutex();
	static void init();
private:
	static pthread_mutex_t _mutex;
};

pthread_mutex_t mutex::_mutex;

mutex::mutex() {
	pthread_mutex_lock(&_mutex);
}

void mutex::init() {
	pthread_mutex_init(&_mutex, NULL);
}

mutex::~mutex() {
	pthread_mutex_unlock(&_mutex);
}







void _trace(const wchar_t* s)
{
	mutex mu;
	{
		std::wofstream ofs("application.log", std::ios::app);
		const auto enc = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << L" [TRACE] " << s << std::endl;
		ofs.close();
	}
	{
		const auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		std::wcout << L" [TRACE] " << s << std::endl;
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

void* thread_func(void* param) {
	_trace(L"<thread_func()> $$$ start $$$");
	int* status = (int*)param;
	*status = 1;
	_trace(L"<thread_func()> Thread is ready.");
	for (int i = 0; i < 10; i++) {
		_trace(L"<thread_func()> .");
		usleep(10000);
	}
	_trace(L"<thread_func()> --- exit ---");
	return NULL;
}

void init() {

	setlocale(LC_ALL, "");
	// setlocale(LC_CTYPE, "ja_JP.UTF-8");

	mutex::init();
}

pthread_t create_thread() {

	pthread_t thread_id = 0;
	volatile int status = 0;
	int error = pthread_create(&thread_id, NULL, thread_func, (void*)&status);
	if (error != 0) {
		_trace(L"[ERROR] スレッドを作成できませんでした...");
		return 0;
	}
	while (status == 0) {
		_trace(L"<main()> スレッドを起動しています...");
		usleep(10);
	}
	return thread_id;
}

int main(int argc, char* argv[]) {

	init();

	_trace(L"<main()> ### start ###");
	_trace(L"<main()> スレッドを起動しています...");
	pthread_t thread_id = 0;
	volatile int status = 0;
	int error = pthread_create(&thread_id, NULL, thread_func, (void*)&status);
	if (error != 0) {
		_trace(L"[ERROR] スレッドを作成できませんでした...");
		return 0;
	}
	while (status == 0) {
		_trace(L"<main()> スレッドを起動しています...");
		usleep(10);
	}

	// スレッドが終了するまで待機しています。
	_trace(L"<main()> スレッドが終了するのを待っています...");
	pthread_join(thread_id, NULL);

	_trace(L"<main()> --- end ---");
	return 0;
}
