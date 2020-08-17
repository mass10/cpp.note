#include <random>

int main() {

	std::random_device r;
	for (int i = 0; i < 10; i++ ) {
		unsigned int next = r();
		printf("%d\n", next);
	}
	return 0;
}

