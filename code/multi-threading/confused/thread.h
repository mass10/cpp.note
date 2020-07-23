#pragma once

#include <string>
#include <Windows.h>

enum class thread_state
{
	ready,
	running,
	closing
};

class thread
{
public:
	thread();
	~thread();
	void run();
	void wait();
	void cancel();
	bool alive() const;
	thread_state get_current_state() const;
private:
	static unsigned __stdcall thread_func(void* thread_param);
	void main();
	std::wstring get_request() const;
	unsigned int _thread_id;
	volatile thread_state _state;
	std::wstring _request;
	HANDLE _thread_handle;
};

