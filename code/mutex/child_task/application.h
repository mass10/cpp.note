#pragma once

#include <Windows.h>
#include <tchar.h>
#include "..\common\framework.h"

///////////////////////////////////////////////////////////////////////////////
// アプリケーション本体

class application {
public:
	application();
	~application();
	void run();
private:
	void speak(const _TCHAR* message) const;
	const string _face;
};
