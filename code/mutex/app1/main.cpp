// UTF-8 with BOM

#include "common.h"
#include <Windows.h>
#include <random>
#include <iostream>
#include "..\common\util.h"
#include "..\common\mutex.h"

void _trace(const _TCHAR* message) {

	const DWORD process_id = GetCurrentProcessId();
	_tprintf(_T("%s [TRACE] [process %d] %s\n"), get_current_timestamp().c_str(), process_id, message);
	fflush(stdout);
}

class application {
public:
	void run();
};

void application::run() {

	std::random_device generator;
	const unsigned int task_id = generator();

	{
		mymutex lock;
		_trace(_T("入店～"));
	}

	const unsigned long long start_tick = GetTickCount64();

	for (int i = 0; ; i++) {

		// 経過時間
		const unsigned long long current_tick = GetTickCount64();
		const unsigned long long elapsed_tick = current_tick - start_tick;
		if (20000 <= elapsed_tick) {
			break;
		}

		mymutex lock;
		_trace(_T("わたしの歌ーーーーー！"));
		_trace(_T("(- ◇ -) アアア～♪ <1番"));
		Sleep(900);
		_trace(_T("(- ◇ -) アアア～♪ <2番"));
		Sleep(900);
		_trace(_T("つかれた...\n"));
	}

	{
		mymutex lock;
		_trace(_T("退出..."));
	}
}

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_tsetlocale(LC_ALL, _T("Japanese"));

	application app;
	app.run();
}
