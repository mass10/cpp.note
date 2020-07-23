// confused.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "thread.h"
#include "logger.h"
#include "critical_section.h"


int main()
{
	remove("cunfused.log");

	logger::trace(_T("<main()> ### start ###"));

	thread th1;
	thread th2;
	thread th3;
	thread th4;
	thread th5;
	thread th6;

	th1.run();
	th2.run();
	th3.run();
	th4.run();
	th5.run();
	th6.run();

	th1.wait();
	th2.wait();
	th3.wait();
	th4.wait();
	th5.wait();
	th6.wait();

	logger::trace(_T("<main()> --- end ---"));
}
