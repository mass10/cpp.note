#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void leaking_operation1() {

	printf("[TRACE] <leaking_operation1()> $$$ start $$$\n");

	char* buffer = (char*)malloc(10);
	strcpy(buffer, "aaabbbccc");

	// バッファオーバーランも Valgrind によって検出されます。
	buffer[10] = 0x00;

	printf("[TRACE] <leaking_operation1()> --- end ---\n");
}

void leaking_operation2() {

	printf("[TRACE] <leaking_operation2()> $$$ start $$$\n");

	char* buffer = new char[10];
	strcpy(buffer, "xxxyyyzzz");

	printf("[TRACE] <leaking_operation2()> --- end ---\n");
}
