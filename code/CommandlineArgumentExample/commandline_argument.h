#pragma once

#include "stdafx.h"
#include <map>

// コマンドライン引数の解析器
class commandline_argument
{
public:
	static commandline_argument& get_instance();
	void configure(const _TCHAR* const argv[]);
	void dump() const;
private:
	commandline_argument();
	~commandline_argument();
	std::map<string, string> _map;
	static commandline_argument _instance;
};
