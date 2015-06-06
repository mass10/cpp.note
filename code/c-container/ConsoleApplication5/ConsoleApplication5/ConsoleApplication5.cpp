// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "container.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand((int)time(NULL));


	x_list* list = NULL;

	int i = 0;
	for (int i = 0; i < 15; i++) {
		char id[16];
		char name[256];
		sprintf(id, "{id: %d}", i);
		sprintf(name, "%d", rand());
		list = a_append_list(list, id, name);
		printf("アドレス [%016X]\n", list);
	}

	//BOM をつけたらコメント中の日本語についても何も言われなくなった...
	//a_list_clear(list);

	return 0;
}

