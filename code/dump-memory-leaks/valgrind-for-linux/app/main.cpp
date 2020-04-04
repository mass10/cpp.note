#include <stdio.h>
#include <string.h>
#include "lib.h"

int main(int argc, char* argv[]) {

	printf("[TRACE] <main()> ### START ###\n");

	leaking_operation1();
	leaking_operation2();

	printf("[TRACE] <main()> --- END ---\n");

	return 0;
}
