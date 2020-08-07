//
//
//
#include <Windows.h>
#include <psapi.h>
#include <vector>

void test1()
{
	std::vector<DWORD> ids(99);
	DWORD affected = 0;
	if (!EnumProcesses(&ids[0], ids.size() * sizeof(DWORD), &affected))
	{
		return;
	}
	for (auto& e : ids)
	{
		wprintf(L"0x%08X\n", e);
	}
}

int wmain(int argc, wchar_t* argv[])
{
	return 0;
}
