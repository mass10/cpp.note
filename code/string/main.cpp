#include <stdio.h>
#include <string>

void test00() {

	std::string s;
	s.append("111", 3);
	printf("[%s] %lu, %lu, %lu\n", s.c_str(), s.length(), s.size(), s.capacity());
	s.append("", 1);
	printf("[%s] %lu, %lu, %lu\n", s.c_str(), s.length(), s.size(), s.capacity());
	s.append("111", 3);
	printf("[%s] %lu, %lu, %lu\n", s.c_str(), s.length(), s.size(), s.capacity());
}

int main(int argc, char* argv[]) {

	test00();
	return 0;
}

