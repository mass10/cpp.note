// app.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <memory>
#include <locale.h>

class pool_manager;
class pool_manager
{
public:
	pool_manager();
	~pool_manager();
	static std::shared_ptr<pool_manager> get_instance();
	const char* get1() const;
private:
	static std::shared_ptr<pool_manager> _instance;
};

std::shared_ptr<pool_manager> pool_manager::_instance = nullptr;

pool_manager::pool_manager()
{
	printf("[TRACE] %p\n", this);
}

const char* pool_manager::get1() const
{
	return "<pool_manager> Hello!";
}

pool_manager::~pool_manager()
{
	printf("(destroyed %p)\n", this);
}

std::shared_ptr<pool_manager> pool_manager::get_instance()
{
	if (_instance == nullptr)
	{
		auto instance = new pool_manager;
		_instance = std::shared_ptr<pool_manager>(instance);
	}
	return _instance;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	setlocale(LC_ALL, "Japanese");

	printf("### start ###\n");

	if (true)
	{
		auto man = pool_manager::get_instance();
		printf("0x%p %s\n", man.get(), man->get1());
	}

	if (true)
	{
		auto man = pool_manager::get_instance();
		printf("0x%p %s\n", man.get(), man->get1());
	}

	if (true)
	{
		auto man = pool_manager::get_instance();
		printf("0x%p %s\n", man.get(), man->get1());
	}

	printf("--- end ---\n");

    return 0;
}
