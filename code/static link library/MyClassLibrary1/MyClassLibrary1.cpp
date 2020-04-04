// MyClassLibrary1.cpp : スタティック ライブラリ用の関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include <string>
#include "MyClassLibrary1.h"

namespace abcde1
{
	std::string hello()
	{
		return "hello!";
	}

	std::wstring MyUtilClass1::trim(const wchar_t* s)
	{
		std::wstring response;
		bool start = false;
		for (const wchar_t* pos = s; *pos; pos++)
		{
			const wchar_t letter = *pos;
			if (start)
			{
				if (letter == L' ') break;
				if (letter == L'\t') break;
				if (letter == L'\r') break;
				if (letter == L'\n') break;
				response += letter;
			}
			else
			{
				if (letter == L' ') continue;
				if (letter == L'\t') continue;
				if (letter == L'\r') continue;
				if (letter == L'\n') continue;
				start = true;
			}
		}
		return response;
	}

	std::string MyUtilClass1::trim(const char* s)
	{
		std::string response;
		bool start = false;
		for (const char* pos = s; *pos; pos++)
		{
			const char letter = *pos;
			if (start)
			{
				if (letter == L' ') break;
				if (letter == L'\t') break;
				if (letter == L'\r') break;
				if (letter == L'\n') break;
				response += letter;
			}
			else
			{
				if (letter == L' ') continue;
				if (letter == L'\t') continue;
				if (letter == L'\r') continue;
				if (letter == L'\n') continue;
				response += letter;
				start = true;
			}
		}
		return response;
	}
}
