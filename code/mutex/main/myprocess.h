#pragma once

#include "string.h"
#include <Windows.h>
#include <tchar.h>

// 外部コマンドを実行します。
class process
{
public:
	// コンストラクター
	//
	// @param `path` コマンドのパス
	process(const _TCHAR* path);
	// デストラクター
	~process();
	// プロセスの終了を待機します。
	void join();

private:
	// プロセス起動時の情報
	STARTUPINFO startup_info;
	// 実行されたプロセスに関する情報
	PROCESS_INFORMATION process_info;
};
