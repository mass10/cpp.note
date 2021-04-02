// UTF-8 with BOM

#include "common.h"
#include <Windows.h>
#include <random>
#include <iostream>
#include "..\common\util.h"
#include "..\common\mutex.h"

///////////////////////////////////////////////////////////////////////////////
// アプリケーション本体
class application {
public:
	void run();
};

void application::run() {

	std::random_device generator;
	const unsigned int task_id = generator();

	_trace(_T("(^ ◇ ^) 入店～"));

	const unsigned long long start_tick = GetTickCount64();

	for (int i = 0; ; i++) {

		// 経過時間
		const unsigned long long current_tick = GetTickCount64();
		const unsigned long long elapsed_tick = current_tick - start_tick;
		if (600 * 3 <= elapsed_tick) {
			break;
		}

		// ※※※ 連続した走査の排他ロック ※※※
		mymutex lock;
		_trace(_T("(^ ◇ ^) ★わたしの歌ーーーーー！"));
		_trace(_T("(^ ◇ ^) アアア～♪ <1番"));
		Sleep(200);
		_trace(_T("(^ ◇ ^) アアア～♪ <2番"));
		Sleep(200);
		_trace(_T("(~ ◇ ~) つかれた..."));
	}

	_trace(_T("(- ◇ -) 退出..."));
}

///////////////////////////////////////////////////////////////////////////////
// アプリケーションのエントリーポイント
int main() {

	// メモリ診断
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ロケール設定
	_tsetlocale(LC_ALL, _T("Japanese"));

	// アプリケーション実行
	application app;
	app.run();

	return 0;
}
