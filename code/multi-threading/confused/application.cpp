#include <stdio.h>
#include "application.h"
#include "critical_section.h"

application application::_instance;

application::application()
{
	printf("<application::application()>\n");
}

application::~application()
{
	printf("<application::~application()>\n");
}
