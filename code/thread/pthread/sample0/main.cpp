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


pthread_mutex_t __mutex;

class mutex {
public:
	mutex();
	~mutex();
};

mutex::mutex() {
	pthread_mutex_lock(&__mutex);
}

mutex::~mutex() {
	pthread_mutex_unlock(&__mutex);
}

void* thread_func(void* param) {

	{
		mutex mu;
		printf("[TRACE] <thread_func()> $$$ start $$$\n");
	}

	int* status = (int*)param;
	*status = 1;

	for (int i = 0; i < 10; i++) {
		{
			mutex mu;
			printf("[TRACE] <thread_func()> .\n");
		}
		usleep(10000);
	}

	{
		mutex mu;
		printf("[TRACE] <thread_func()> --- exit ---\n");
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	pthread_mutex_init(&__mutex, NULL);

	{
		mutex mu;
		printf("[TRACE] <main()> ### start ###\n");
		printf("[TRACE] <main()> creating thread...\n");
	}

	// setlocale(LC_CTYPE, "ja_JP.UTF-8");

	// スレッドを起動しています。
	volatile int status = 0;
	pthread_t thread_id = 0;
	// pthread_attr_t attr;
	// pthread_attr_init(&attr);
	int error = pthread_create(&thread_id, NULL, thread_func, (void*)&status);
	if (error != 0) {
		mutex mu;
		printf("[ERROR] cannot create a new thread...\n");
		return 0;
	}

	{
		mutex mu;
		printf("[TRACE] <main()> thread id: [%lu]\n", thread_id);
	}

	// スレッドが起動するまで待機しています。
	while (status == 0) {
		{
			mutex mu;
			printf("[TRACE] <main()> .\n");
		}
		usleep(10);
	}

	// スレッドが終了するまで待機しています。
	pthread_join(thread_id, NULL);

	{
		mutex mu;
		printf("[TRACE] <main()> --- end ---\n");
	}

	return 0;
}
