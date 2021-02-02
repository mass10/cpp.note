#pragma once

#include <string>

#ifdef UNICODE
typedef std::wstring string;
#else
typedef std::string string;
#endif

// 文字列ユーティリティ
class string_utils
{
public:
	static bool starts_with(const string& left, const _TCHAR* right);
	static bool ends_with(const string& left, const _TCHAR* right);
	static void upper(string& left);
	static void lower(string& left);
private:
	string_utils();
	~string_utils();
};
