// coding: utf-8
#include <glib.h>
#include <stdio.h>
#include <time.h>

GList* _push(GList* list, char* text) {

	GList* new_list = g_list_append(list, text);
	printf("list:[%016X]->[%016X] 現在のアカウント数: %d (%s)\n",
		list,
		new_list,
		g_list_length(new_list),
		list == new_list ? "アドレス変化なし" : "リストが再構築された");
	return new_list;
}

int main(int argc, char* argv[]) {

	GList* list = NULL;
	int i = 0;



	rand(time(NULL));

	list = g_list_alloc();

	for(i = 0; i < 10000; i++) {
		char buffer[1024];
		sprintf(buffer, "{id: %d}", i);
		list = _push(list, buffer);
	}

	list = _push(list, "Kiyoshi Nakahata");
	list = _push(list, "Masayuki Kakefu");
	list = _push(list, "Hiromi Go");

	g_list_free(list);

	return 0;
}

