#include "stdafx.h"
#include "string.h"

bool string_utils::starts_with(const string& left, const _TCHAR* right)
{
	if (left[0] == 0x00)
		return false;
	if (right[0] == 0x00)
		return false;

	for (unsigned int i = 0; ; i++)
	{
		if (right[0] == 0x00)
			// ここまで完全に一致
			return true;

		if (left[i] == right[i])
			continue;

		break;
	}

	return false;
}
