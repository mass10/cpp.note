// test1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <sstream>
#include <tchar.h>
#include "logger.h"

int main()
{
	setlocale(LC_ALL, "Japanese");
	_wsetlocale(LC_ALL, _T("Japanese"));

	logger(std::wstringstream() << _T("### START ###"));
	logger(std::wstringstream() << _T("コニチハ！"));
	logger(std::wstringstream() << _T("-- END ---"));
}
