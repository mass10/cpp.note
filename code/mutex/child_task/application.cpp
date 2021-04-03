#include "application.h"

string choose_face_aa() {

	SYSTEMTIME time = {};
	GetLocalTime(&time);

	auto timestamp = time.wMilliseconds;

	auto seed = timestamp % 5;
	switch (seed) {
	case 0: return _T("(= ◇ =)");
	case 1: return _T("(\\ ◇ \\)");
	case 2: return _T("(゜◇゜)");
	case 3: return _T("(^ ◇ ^)");
	default: return _T("(- ◇ -)");
	}
}

application::application() :
	_face(choose_face_aa())
{

}

void application::speak(const _TCHAR* message) const {

	log_trace(this->_face + _T(" ") + message);
}

void application::run() {

	this->speak(_T(" 入店～"));

	const unsigned long long start_tick = GetTickCount64();

	for (int i = 0; ; i++) {

		// 経過時間
		const unsigned long long current_tick = GetTickCount64();
		const unsigned long long elapsed_tick = current_tick - start_tick;

		if (600 * 3 <= elapsed_tick) {
			break;
		}

		// ※※※ 自分の歌まで待機 ※※※
		mymutex lock;

		this->speak(_T("★わたしの歌ーーーーー！"));
		this->speak(_T("アアア～♪ <1番"));
		Sleep(200);
		this->speak(_T("アアア～♪ <2番"));
		Sleep(200);
		this->speak(_T("つかれた..."));
	}

	this->speak(_T("退出..."));
}

application::~application() {

}
