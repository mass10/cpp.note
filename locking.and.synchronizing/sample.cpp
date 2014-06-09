#include <pthread.h>

class critical_section
{
public:
	critical_section();
	~critical_section();
	static void init();
	static void destroy();
private:
	critical_section(const critical_section& other);
	critical_section& operator = (const critical_section& other);
	static pthread_mutex_t _mutex;
};

pthread_mutex_t critical_section::_mutex;

critical_section::critical_section() {
	int result = pthread_mutex_lock(&_mutex);
	if(0 != result) {
		perror(NULL);
	}
}

critical_section::~critical_section() {
	int result = pthread_mutex_unlock(&_mutex);
	if(0 != result) {
		perror(NULL);
	}
}

void critical_section::init() {
	pthread_mutexattr_t a;
	pthread_mutexattr_init(&a);
	pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&_mutex, &a);
}

void critical_section::destroy() {
	pthread_mutex_destroy(&_mutex);
}

void _synchronizing() {

	critical_section locked;

	// 同期したい処理
}

int main(int argc, char* argv[]) {

	critical_section::init();
	_synchronizing();
	critical_section::destroy();
	return 0;
}