﻿// UTF-8 with BOM

#include <Windows.h>
#include <crtdbg.h>
#include <tchar.h>
#include <locale.h>
#include "application.h"

// エントリーポイント
int _tmain(int argc, _TCHAR* argv[]) {

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	// メモリ診断
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ロケール設定
	_tsetlocale(LC_ALL, _T("Japanese"));

	// アプリケーション実行
	application app;
	app.run();

	return 0;
}
