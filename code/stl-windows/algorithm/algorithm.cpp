//
// Standard Template Library を使用した文字列の加工です。
//

#include <algorithm>
#include <stdio.h>
#include <string>
#include <locale>

std::wstring to_upper(const std::wstring& s)
{
	std::wstring result;
	std::locale loc;
	for (auto& c : s)
	{
		const wchar_t letter = std::toupper(c, loc);
		wprintf(L"[%c] >> [%c]\n", c, letter);
		result += (letter);
	}
	return result;
}

std::wstring to_lower_x(const std::wstring& s)
{
	// XXX 全角文字を破壊します。
	std::wstring result = s;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

std::wstring to_lower(const std::wstring& s)
{
	std::wstring result;
	std::locale loc;
	for (auto& c : s)
	{
		const wchar_t letter = std::tolower(c, loc);
		wprintf(L"[%c] >> [%c]\n", c, letter);
		result += (letter);
	}
	return result;
}

int wmain(int argc, wchar_t* argv[])
{
	_wsetlocale(LC_ALL, L"Japanese");

	// サンプル
    std::wstring s = L"Jimi Hendrix. Ｊｉｍｉ　Ｈｅｎｄｒｉｘ ジミー～";

	s = to_lower(s);
	wprintf(L"lower case: [%s]\n", s.c_str());

	s = to_upper(s);
	wprintf(L"upper case: [%s]\n", s.c_str());

	return 0;
}
