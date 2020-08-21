// UTF-8 with BOM
#pragma once

#include <string>
#include <sstream>

#ifdef UNICODE
typedef std::wstring string;
typedef std::wstringstream stringstream;
#else
typedef std::string string;
typedef std::stringstream stringstream;
#endif
