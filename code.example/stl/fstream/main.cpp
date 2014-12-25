#include <stdio.h>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

	std::ifstream f("main.cpp");
	long lines = 0;
	while(true) {
		std::string line = "";
		if(!std::getline(f, line))
			break;
		std::cout << lines << ": " << line << std::endl;
		lines++;
	}
	return 0;
}
