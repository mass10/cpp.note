// win32.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

std::wstring get_current_timestamp()
{
	SYSTEMTIME s;
	GetLocalTime(&s);

	_TCHAR buffer[24];
	_stprintf_s(buffer, sizeof(buffer) / sizeof(_TCHAR),
		_T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds);

	return buffer;
}


int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_tsetlocale(LC_ALL, L"Japanese");

	const std::wstring current_timestamp = get_current_timestamp();
	_tprintf(_T("タイムスタンプ: %s\n"), current_timestamp.c_str());

	return 0;
}
