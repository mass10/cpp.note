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

	printf("[TRACE] <thread_func()> thread started!\n");
	int* status = (int*)param;
	*status = 1;
	// sleep(3);
	printf("[TRACE] <thread_func()> thread exit!\n");
	return NULL;
}

int main(int argc, char* argv[]) {

	volatile int status = 0;
	setlocale(LC_CTYPE, "ja_JP.UTF-8");
	pthread_t thread_id = 0;
	// pthread_attr_t attr;
	// pthread_attr_init(&attr);
	printf("[TRACE] <thread_func()> creating thread...\n");
	int error = pthread_create(&thread_id, NULL, thread_func, (void*)&status);
	printf("[TRACE] %d\n", error);
	if (error != 0) {
		printf("[ERROR] cannot create a new thread...\n");
		return 0;
	}
	while (status == 0) {
		printf(".\n");
		sleep(0.1);
	}
	pthread_join(thread_id, NULL);
	printf("[TRACE] thread id: [%lu]\n", thread_id);
	return 0;
}
