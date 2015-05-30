#include <stdio.h>
#include <string>
#include <list>
#include <iostream>

void erase(std::list<std::string>& list) {

	list.clear();
}

void diagnose(const std::list<std::string>& list) {

	for(std::list<std::string>::const_iterator i = list.begin(); i != list.end(); i++) {

		// const リストなので要素の const を解除することはできない
		//std::string& s = *i;
		const std::string& s = *i;
		std::cout << "\"" << s << "\"" << std::endl; 

		// const 要素の値を書き換えることはできない
		//s = "";
	}

	// const リストに変更を加えることはできない
	//list.clear();

	// リストに変更を加える操作に const リストを渡すことはできない
	//erase(list);
}

int main(int argv, char* argc[]) {

	std::list<std::string> list;
	list.push_back("A");
	list.push_back("B");
	list.push_back("C");
	diagnose(list);
	return 0;
}

