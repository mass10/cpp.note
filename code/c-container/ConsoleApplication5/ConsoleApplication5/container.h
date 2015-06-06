#pragma once

#if __cplusplus
extern "C" {
#endif

typedef struct _x_list {
	char* id;
	char* data;
	struct _x_list* next;
} x_list;

x_list* a_append_list(x_list* list, const char* id, const char* data);

x_list* a_list_end(x_list* list);

void a_list_clear(x_list* e);

#if __cplusplus
}
#endif
