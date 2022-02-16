#include <stdio.h>
#include <Windows.h>

// ほんとにこれでいいの？
// (ENABLE_VIRTUAL_TERMINAL_PROCESSING の定義がみつからない)
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 4
#endif

//
// アプリケーションのエントリーポイントです。
//
int _tmain(int argc, const _TCHAR* argv[])
{
	UNREFERENCED_PARAMETER(argc);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD consoleMode = 0;
  GetConsoleMode(stdOut, &consoleMode);
  consoleMode = consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(stdOut, consoleMode);

	_tsetlocale(LC_ALL, _T("Japanese"));

	_tprintf(_T("\x1b[32mHELLOOOOOOOOOOOOOO\x1b[39m\n"));
  
  return 0;
}

