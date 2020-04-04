#include <windows.h>
#include <string.h>
#include <crtdbg.h>

void leak()
{
	{
		char* buffer = (char*)malloc(10);
		if (buffer == NULL)
		{
			return;
		}
		strcpy_s(buffer, 10, "aaabbbccc");
	}

	{
		char* buffer = new char[10];
		strcpy_s(buffer, 10, "XXXYYYZZZ");
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	leak();
}

/*
Detected memory leaks!
Dumping objects ->
{79} normal block at 0x01243AE0, 10 bytes long.
 Data: <XXXYYYZZZ > 58 58 58 59 59 59 5A 5A 5A 00
{78} normal block at 0x01243AA8, 10 bytes long.
 Data: <aaabbbccc > 61 61 61 62 62 62 63 63 63 00
Object dump complete.
*/
