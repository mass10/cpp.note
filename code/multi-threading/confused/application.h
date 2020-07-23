#pragma once

#include "critical_section.h"

class application
{
public:

private:

	application();

	~application();

	static application _instance;

	critical_section_lifetime _critical_section_lifetime;
};
