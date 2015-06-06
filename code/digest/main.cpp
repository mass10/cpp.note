#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <openssl/sha.h>

//
// C++ を使用したダイジェストのサンプル
//

std::string digest_sha1(const char* p) {

	unsigned char result[1024] = "";
	SHA1((unsigned char*)p, strlen(p), result);
	std::string response;
	for(const unsigned char* p = result; *p; p++) {
		char buffer[3];
		sprintf(buffer, "%02x", *p);
		response += buffer;
	}
	return response;
}

int main(int argc, char* argv[]) {

	std::string s = "あいうえお\n";

	std::cout << "[" << digest_sha1(s.c_str()) << "]" << std::endl;

	return 0;
}

