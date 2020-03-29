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

void _footstep(const char* s) {
	mutex mu;
	std::cout << s << std::endl;
}

void* thread_func(void* param) {
	_footstep("[TRACE] <thread_func()> $$$ start $$$");
	int* status = (int*)param;
	*status = 1;
	_footstep("[TRACE] <thread_func()> Thread is ready.");
	for (int i = 0; i < 10; i++) {
		_footstep("[TRACE] <thread_func()> .");
		usleep(10000);
	}
	_footstep("[TRACE] <thread_func()> --- exit ---");
	return NULL;
}

int main(int argc, char* argv[]) {

	mutex::init();

	_footstep("[TRACE] <main()> ### start ###");

	// setlocale(LC_CTYPE, "ja_JP.UTF-8");

	// スレッドを起動しています。
	_footstep("[TRACE] <main()> creating thread...");
	volatile int status = 0;
	pthread_t thread_id = 0;
	// pthread_attr_t attr;
	// pthread_attr_init(&attr);
	int error = pthread_create(&thread_id, NULL, thread_func, (void*)&status);
	if (error != 0) {
		_footstep("[ERROR] cannot create a new thread...");
		return 0;
	}
	_footstep("[TRACE] <main()> Waiting for thread ready.");

	// スレッドが起動するまで待機しています。
	while (status == 0) {
		_footstep("[TRACE] <main()> .");
		usleep(10);
	}

	// スレッドが終了するまで待機しています。
	_footstep("[TRACE] <main()> Waiting for thread exit.");
	pthread_join(thread_id, NULL);

	_footstep("[TRACE] <main()> --- end ---");
	return 0;
}
