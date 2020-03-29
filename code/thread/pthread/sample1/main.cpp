#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
// #include <wchar.h>
// #include <locale.h>
// #include <clocale>
// #include <codecvt>
// #include <process.h>




///////////////////////////////////////////////////////////////////////////////

pthread_mutex_t __mutex;

class mutex {
public:
	mutex();
	~mutex();
};

mutex::mutex() {
	pthread_mutex_lock(&__mutex);	
}

mutex::~mutex() {
	pthread_mutex_unlock(&__mutex);	
}

void _footstep(const char* s) {
	mutex mu;
	std::cout << s << std::endl;
}








///////////////////////////////////////////////////////////////////////////////

enum class thread_state {
	ready,
	up,
	exit
};

class thread_core {
public:
	thread_core();
	~thread_core();
	void run();
	void main();
	void wait();
private:
	static void* thread_func(void* param);
	void close();
	int _thread_handle;
	int _thread_id;
	void set_state(thread_state state);
	thread_state get_status();
	unsigned int get_thread_id();
	volatile thread_state _state;
};

thread_core::thread_core() {

	this->_thread_id = 0;
	this->_state = thread_state::ready;
}

thread_core::~thread_core() {

	this->wait();
}

void thread_core::set_state(thread_state state) {

	mutex mu;
	this->_state = state;
}

thread_state thread_core::get_status() {

	mutex mu;
	return this->_state;
}

void thread_core::close() {

}

unsigned int thread_core::get_thread_id() {
	mutex mu;
	return this->_thread_id;
}

void thread_core::wait() {

	const unsigned thread_id = this->get_thread_id();
	if (thread_id == 0) return;
	_footstep("[TRACE] <thread_core::wait()> スレッドが終わるのを待っています...");
	// ★★★ Segmentation fault!!! ★★★
	// pthread_join(thread_id, NULL);
	while (this->get_status() != thread_state::exit) {
		usleep(10);
	}
	this->_thread_id = 0; // SAFE
}

void thread_core::main() {

	_footstep("[TRACE] <thread_core::main()> $$$ begin $$$");
	this->_thread_id = pthread_self();
	this->set_state(thread_state::up);
	for (int i = 0; i < 10; i++) {
		_footstep("[TRACE] <thread_core::main()> (.)");
		usleep(100000);
	}
	// sleep(5);
	_footstep("[TRACE] <thread_core::main()> --- end ---");
	this->set_state(thread_state::exit);
}

void* thread_core::thread_func(void* param) {

	_footstep("[TRACE] <thread_core::thread_func()> thread started!");
	thread_core* t = (thread_core*)param;
	t->main();
	_footstep("[TRACE] <thread_core::thread_func()> thread exit.");
	pthread_exit(NULL);
	return NULL;
}

void thread_core::run() {

	pthread_t thread_id = 0;
	// pthread_attr_t attr;
	// pthread_attr_init(&attr);
	_footstep("[TRACE] <thread_core::run()> creating thread...");
	int error = pthread_create(&thread_id, NULL, thread_core::thread_func, (void*)this);
	if (error != 0) {
		_footstep("[ERROR] <thread_core::run()> cannot create a new thread...");
		return;
	}
	_footstep("[TRACE] <thread_core::run()> (waiting for thread up...)");
	while (this->get_status() == thread_state::ready) {
		_footstep("[TRACE] <thread_core::run()> .");
		usleep(100);
	}
}

///////////////////////////////////////////////////////////////////////////////

class application {
public:
	application();
	~application();
	void run();
};

application::application() {

}

application::~application() {

}

void application::run() {

	_footstep("### start ###");

	thread_core t1;
	thread_core t2;
	thread_core t3;

	t1.run();
	t2.run();
	t3.run();

	t1.wait();
	t2.wait();
	t3.wait();

	_footstep("--- end ---");
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

	// setlocale(LC_CTYPE, "ja_JP.UTF-8");

	pthread_mutex_init(&__mutex, NULL);

	application app;
	app.run();

	return 0;
}
