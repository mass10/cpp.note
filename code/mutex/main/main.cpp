// UTF-8 with BOM

#include <Windows.h>
#include <crtdbg.h>
#include <tchar.h>
#include "string.h"
#include "myprocess.h"
#include "..\common\mutex.h"
#include "..\common\util.h"

// アプリケーション本体
class application {
public:
	void run();
};

void application::run() {

	log_trace(_T("### 開始 ###"));

	{
		process process1(_T("child_task.exe"));
		process process2(_T("child_task.exe"));
		process process3(_T("child_task.exe"));
		process process4(_T("child_task.exe"));
		process process5(_T("child_task.exe"));
	}

	log_trace(_T("--- 終了 ---"));
}

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
