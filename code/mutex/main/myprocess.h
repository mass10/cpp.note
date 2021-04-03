#pragma once

#include "string.h"
#include <Windows.h>
#include <tchar.h>

class process
{
public:
	process(const _TCHAR* path);
	~process();
	void join();

private:
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
};
