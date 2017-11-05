#include <stdio.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

int main() {

	// 生成
	const boost::uuids::uuid id = boost::uuids::random_generator()();

	// stream operator
	{
		std::stringstream s;
		s << id;
		std::cout << "[" << s.str() << "]\n";
	}

	{
		std::string s = boost::lexical_cast<std::string>(id);
		printf("[%s]\n", s.c_str());
	}

	{
		std::string s = to_string(id);
		printf("[%s]\n", s.c_str());
	}

	return 0;
}
