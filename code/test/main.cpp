#include <stdio.h>
#include <stddef.h>
#include <iostream>

class Klass {
	int value;
};

class Data {
public:
	int a;
	Klass *klass;
	long lvalue0;
	long lvalue1;
};

void _test(const Data* data) {

	// const void* pos = &((Data*)data)->klass;
	// const size_t offset = (size_t)&((Data*)data)->klass;
	const size_t offset = (size_t)&((Data*)data)->klass;
	printf("[0x%08x]\n", (void*)offset);
	// printf("[0x%08x]\n", (void*)data->klass);
}

#define _dump_offset(base, child) \
	{ \
		size_t offset_by_offsetof = offsetof(base, child); \
		std::cout << "offset_by_offsetof " << offset_by_offsetof << std::endl; \
	} \

int main() {

	_test((Data*)NULL);

	size_t offset = (size_t)& ((Data*)0)->klass;
	std::cout << "offset " << offset << std::endl;

	_dump_offset(Data, klass);
	_dump_offset(Data, a);
	_dump_offset(Data, lvalue0);
	_dump_offset(Data, lvalue1);

	printf("[%s]\n", __func__);
}




