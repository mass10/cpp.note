#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wchar.h>
#include <locale.h>
#include <clocale>
#include <codecvt>




// ミューテックスの定義
class mutex {
public:
	// コンストラクター
	mutex();
	// デストラクター
	~mutex();
	// ミューテックスを初期化します。
	static void initialize();
private:
	// ミューテックスオブジェクト
	static pthread_mutex_t __mutex;
};

pthread_mutex_t mutex::__mutex;

void mutex::initialize() {
	pthread_mutex_init(&__mutex, NULL);
}

mutex::mutex() {
	pthread_mutex_lock(&__mutex);	
}

mutex::~mutex() {
	pthread_mutex_unlock(&__mutex);	
}






void _trace(const wchar_t* s)
{
	mutex mu;

	// to file
	{
		std::wofstream ofs("application.log", std::ios::app);
		const auto enc = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << L"[TRACE] " << s << std::endl;
		ofs.close();
	}

	// stdout
	{
		const auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		std::wcout << L"[TRACE] " << s << std::endl;
	}
}

void _trace(const std::wstring& s)
{
	_trace(s.c_str());
}

void _trace(const std::wstringstream& s)
{
	_trace(s.str());
}

void _error(const wchar_t* s)
{
	mutex mu;

	// to file
	{
		std::wofstream ofs("application.log", std::ios::app);
		const auto enc = ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs << L"[ERROR] " << s << std::endl;
		ofs.close();
	}

	// stdout
	{
		const auto enc2 = std::wcout.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		std::wcout << L"[ERROR] " << s << std::endl;
	}
}











///////////////////////////////////////////////////////////////////////////////

enum class thread_state {
	ready,
	up,
	exit
};

class thread_core {
public:
	// コンストラクター
	thread_core(std::wstring name);
	// デストラクター
	~thread_core();
	// タスクの実行
	void run();
	// タスクの終了を待機
	void wait();
private:
	// タスクのメイン処理
	void main();
	// スレッド関数
	static void* thread_func(void* param);
	// 
	int _thread_handle;
	pthread_t _thread_id = 0;
	void set_state(thread_state state);
	thread_state get_status();
	pthread_t get_thread_id();
	volatile thread_state _state;
	std::wstring _name;
};

thread_core::thread_core(std::wstring name) {

	this->_thread_id = 0;
	this->_state = thread_state::ready;
	this->_name = name;
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

pthread_t thread_core::get_thread_id() {
	mutex mu;
	return this->_thread_id;
}

void thread_core::wait() {

	pthread_t thread_id = this->get_thread_id();
	if (thread_id == 0) return;
	_trace(L"<thread_core::wait()> スレッドが終わるのを待っています...");
	pthread_join(thread_id, NULL);
	while (this->get_status() != thread_state::exit) {
		usleep(10);
	}
	this->_thread_id = 0; // SAFE
}

void thread_core::main() {

	_trace(L"<thread_core::main()> $$$ begin $$$");
	// このスレッドの名前
	const std::wstring thread_name = this->_name;
	// このスレッドの ID
	this->_thread_id = pthread_self();
	// ステータスを更新します。
	this->set_state(thread_state::up);
	for (int i = 0; i < 10; i++) {
		std::wstringstream s;
		s << L"<thread_core::main()> (スレッド: " << thread_name << L")";
		_trace(s);
		usleep(100000);
	}
	_trace(L"<thread_core::main()> --- end ---");
	// ステータスを更新します。
	this->set_state(thread_state::exit);
}

void* thread_core::thread_func(void* param) {

	thread_core* t = (thread_core*)param;
	t->main();
	return NULL;
}

void thread_core::run() {

	// このスレッドの名前
	const std::wstring thread_name = this->_name;
	pthread_t thread_id = 0;
	_trace(L"<thread_core::run()> スレッドを作成しています...");
	int error = pthread_create(&thread_id, NULL, thread_core::thread_func, (void*)this);
	if (error != 0) {
		_error(L"<thread_core::run()> スレッドを作成できません...");
		return;
	}
	while (this->get_status() == thread_state::ready) {
		std::wstringstream s;
		s << L"<thread_core::run()> (スレッドが立ち上がるのを待っています... " << thread_name << L")";
		_trace(s);
		usleep(100);
	}
}

///////////////////////////////////////////////////////////////////////////////

class application {
private:
	application();
	~application();
	static application _instance;
public:
	static void startup();
	static application& get_instance();
	void run();
};

// アプリケーションのインスタンス
application application::_instance;

// コンストラクター
application::application() {

}

// アプリケーション開始前の特別な初期化
void application::startup() {

}

// アプリケーションのインスタンスを返します。
application& application::get_instance() {
	return _instance;
}

// デストラクター
application::~application() {

}

// アプリケーションのメイン処理
void application::run() {

	_trace(L"### start ###");

	thread_core t1(L"t1");
	thread_core t2(L"t2");
	thread_core t3(L"t3");

	t1.run();
	t2.run();
	t3.run();

	t1.wait();
	t2.wait();
	t3.wait();

	_trace(L"--- end ---");
}

// エントリーポイント
int main(int argc, char* argv[]) {

	// ロケール設定
	// setlocale(LC_CTYPE, "ja_JP.UTF-8");
	setlocale(LC_CTYPE, "");

	// ミューテックスの初期化
	mutex::initialize();

	// アプリケーション実行
	application::get_instance().startup();
	application::get_instance().run();

	// 終了
	return 0;
}
