#pragma once

#include <Windows.h>

class mymutex
{
public:
	mymutex();
	~mymutex();
private:
	HANDLE _handle;
};
