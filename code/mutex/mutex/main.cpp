#include <Windows.h>
#include <crtdbg.h>
#include <tchar.h>
#include "string.h"
#include "myprocess.h"
#include "..\common\mutex.h"
#include "..\common\util.h"

// アプリケーション本体
class application
{
public:
	void run();
};

void application::run()
{
	_trace(_T("### 開始 ###\n"));

	process process1(_T("app1.exe"));
	process process2(_T("app1.exe"));
	process process3(_T("app1.exe"));
	process process4(_T("app1.exe"));
	process process5(_T("app1.exe"));

	process1.join();
	process2.join();
	process3.join();
	process4.join();
	process5.join();

	_trace(_T("--- 終了 ---\n"));
}

// エントリーポイント
int _tmain(int argc, _TCHAR* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_tsetlocale(LC_ALL, _T("Japanese"));

	application app;
	app.run();

	return 0;
}
