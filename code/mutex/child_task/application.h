#pragma once

#include <Windows.h>
#include <tchar.h>
#include "..\common\framework.h"

// アプリケーション本体の定義
class application {
public:
	// コンストラクター
	application();
	// デストラクター
	~application();
	// アプリケーションを実行します。
	void run();
private:
	// 言葉を話します。
	void speak(const _TCHAR* message) const;
	// このタスクの顔文字
	const string _face;
};
