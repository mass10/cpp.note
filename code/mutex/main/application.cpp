#include "application.h"
#include "myprocess.h"
#include "..\common\framework.h"

application::application() {

}

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

application::~application() {

}
