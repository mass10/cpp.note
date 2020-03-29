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

void* thread_func(void* param) {

	printf("[TRACE] <thread_func()> $$$ start $$$\n");
	int* status = (int*)param;
	*status = 1;

	for (int i = 0; i < 10; i++) {
		printf("[TRACE] <thread_func()> .\n");
		usleep(100);
	}
	printf("[TRACE] <thread_func()> --- exit ---\n");
	return NULL;
}

int main(int argc, char* argv[]) {

	printf("[TRACE] <main()> ### start ###\n");
	volatile int status = 0;
	// setlocale(LC_CTYPE, "ja_JP.UTF-8");
	pthread_t thread_id = 0;
	// pthread_attr_t attr;
	// pthread_attr_init(&attr);
	printf("[TRACE] <main()> creating thread...\n");
	int error = pthread_create(&thread_id, NULL, thread_func, (void*)&status);
	if (error != 0) {
		printf("[ERROR] cannot create a new thread...\n");
		return 0;
	}
	printf("[TRACE] <main()> thread id: [%lu]\n", thread_id);
	while (status == 0) {
		printf("[TRACE] <main()> .\n");
		usleep(10);
	}
	pthread_join(thread_id, NULL);
	printf("[TRACE] <main()> --- end ---\n");
	return 0;
}
