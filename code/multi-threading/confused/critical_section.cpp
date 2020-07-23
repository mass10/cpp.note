#include "critical_section.h"

CRITICAL_SECTION critical_section::_section;

void critical_section::init()
{
	memset(&_section, 0x00, sizeof(_section));
	InitializeCriticalSection(&_section);
}

void critical_section::free()
{
	DeleteCriticalSection(&_section);
}

critical_section::critical_section()
{
	EnterCriticalSection(&_section);
}

critical_section::~critical_section()
{
	LeaveCriticalSection(&_section);
}

critical_section_lifetime::critical_section_lifetime()
{
	critical_section::init();
}

critical_section_lifetime::~critical_section_lifetime()
{
	critical_section::free();
}
