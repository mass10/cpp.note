//
// Standard Template Library を使用した文字列の加工です。
//

#include <algorithm>
#include <stdio.h>
#include <string>
#include <locale>

// 超手抜き版。今だけ動けばいいとき。
wchar_t to_upper(wchar_t c)
{
	if ('a' <= c && c <= 'z') return c - 32;
	return c;
}

// 超手抜き版。今だけ動けばいいとき。
wchar_t to_lower(wchar_t c)
{
	if ('A' <= c && c <= 'Z') return c + 32;
	return c;
}

// 半角文字のみ変換
wchar_t to_lower_正(wchar_t c)
{
	switch (c)
	{
	case 'A': return 'a';
	case 'B': return 'b';
	case 'C': return 'c';
	case 'D': return 'd';
	case 'E': return 'e';
	case 'F': return 'f';
	case 'G': return 'g';
	case 'H': return 'h';
	case 'I': return 'i';
	case 'J': return 'j';
	case 'K': return 'k';
	case 'L': return 'l';
	case 'M': return 'm';
	case 'N': return 'n';
	case 'O': return 'o';
	case 'P': return 'p';
	case 'Q': return 'q';
	case 'R': return 'r';
	case 'S': return 's';
	case 'T': return 't';
	case 'U': return 'u';
	case 'V': return 'v';
	case 'W': return 'w';
	case 'X': return 'x';
	case 'Y': return 'y';
	case 'Z': return 'z';
	}
	return c;
}

wchar_t to_upper_正(wchar_t c)
{
	switch (c)
	{
	case 'a': return 'A';
	case 'b': return 'B';
	case 'c': return 'C';
	case 'd': return 'D';
	case 'e': return 'E';
	case 'f': return 'F';
	case 'g': return 'G';
	case 'h': return 'H';
	case 'i': return 'I';
	case 'j': return 'J';
	case 'k': return 'K';
	case 'l': return 'L';
	case 'm': return 'M';
	case 'n': return 'N';
	case 'o': return 'O';
	case 'p': return 'P';
	case 'q': return 'Q';
	case 'r': return 'R';
	case 's': return 'S';
	case 't': return 'T';
	case 'u': return 'U';
	case 'v': return 'V';
	case 'w': return 'W';
	case 'x': return 'X';
	case 'y': return 'Y';
	case 'z': return 'Z';
	}
	return c;
}

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
