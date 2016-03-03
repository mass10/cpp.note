#include <stdio.h>
#include <iostream>
#include <string>

namespace Blood {
	// 血液型
	typedef enum Type {X, Y, Z,} Type;
}

namespace Room {
	// 部屋の種類
	typedef enum Type {X, Y, Z,} Type;
}

void _print(Blood::Type t) {

	printf("Blood::Type is [%d]\n", (int)t);
}

void _print(Room::Type t) {

	printf("Room::Type is [%d]\n", (int)t);
}

int main(int argc, char* argv[]) {

	_print(Blood::X);
	_print(Blood::Y);
	_print(Blood::Z);

	_print(Room::X);
	_print(Room::Y);
	_print(Room::Z);

	return 0;
}

