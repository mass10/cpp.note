#include <stdio.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

int main() {
	const boost::uuids::uuid id = boost::uuids::random_generator()();
	std::string s = boost::lexical_cast<std::string>(id);
	printf("[%s]\n", s.c_str());
	return 0;
}
