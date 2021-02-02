#include "stdafx.h"
#include "commandline_argument.h"

commandline_argument commandline_argument::_instance;

commandline_argument::commandline_argument()
{

}

commandline_argument::~commandline_argument()
{

}

commandline_argument& commandline_argument::get_instance()
{
	return _instance;
}

void commandline_argument::dump() const
{
	_tprintf(_T("[TRACE] パラメータのダンプ\n"));
	for (auto& it : this->_map)
	{
		_tprintf(_T("    [%s]=[%s]\n"), it.first.c_str(), it.second.c_str());
	}
}

void commandline_argument::configure(const _TCHAR* const argv[])
{
	string key;

	for (int i = 1; ; i++)
	{
		const _TCHAR* argument = argv[i];
		if (argument == NULL)
			break;

		if (_tcsncmp(argument, _T("--"), 2) == 0)
		{
			// "--" で始まる。
			if (key != _T(""))
			{
				// 前回のキーが保留中。
				this->_map[key] = _T("true");
				key = _T("");
			}

			const _TCHAR* equals = _tcsstr(argument, _T("="));
			if (equals == NULL)
			{
				// "=" なし。このキーを一時保管。
				key = argument;
			}
			else
			{
				key = _T("");
				key.append(argument, equals - argument);
				string value;
				value.append(equals + 1);
				this->_map[key] = value;
				key = _T("");
				value = _T("");
			}
		}
		else
		{
			if (key != _T(""))
			{
				// 前回のキーが保留中。
				this->_map[key] = argument;
				key = _T("");
			}
			else
			{
				_tprintf(_T("[TRACE] パラメータは無視されました。[%s]\n"), argument);
			}
		}
	}

	if (key != _T(""))
	{
		this->_map[key] = _T("true");
		key = _T("");
	}
}
