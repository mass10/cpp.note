#include <stdio.h>
#include <iostream>
#include <string>
#include <boost/algorithm/string/trim.hpp>
#include "main.h"

// static const char* __safe(const char* p) { return p == NULL ? "" : p; }


void logger::info(const char* message) {

	std::string s = message;
	boost::algorithm::trim(s);
	std::cout << "[info] message=[" << s << "]" << std::endl;
}

int main(int argc, char* argv[]) {

	logger::info("           		 ### start ###   	 	 	     ");
	logger::info("  	 	 end   	 	 	 	");
	return 0;
}

