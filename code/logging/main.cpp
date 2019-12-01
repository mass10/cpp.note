







class logger
{
private:

	FILE* _file;

public:

	std::wstring path()
	{
		return _T("myapp.log");
	}

	logger(const _TCHAR* something)
	{
		const _TCHAR* path = _T("myapp.log");
		std::ofstream ofs;
		//ofs.imbue(std::locale("Japanese", LC_COLLATE));
		//ofs.imbue(std::locale("Japanese", LC_CTYPE));
		ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs.open(path, std::ios::app);
		ofs << something << std::endl;
		ofs.close();
	}

	logger(const std::wstring& something)
	{
		const _TCHAR* path = _T("myapp.log");
		std::wofstream ofs;
		//ofs.imbue(std::locale("Japanese", LC_COLLATE));
		//ofs.imbue(std::locale("Japanese", LC_CTYPE));
		ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs.open(path, std::ios::app);
		ofs << something.c_str() << std::endl;
		ofs.close();
	}

private:
	logger(const std::stringstream& something)
	{
		const _TCHAR* path = _T("myapp.log");
		std::ofstream ofs;
		//ofs.imbue(std::locale("Japanese", LC_COLLATE));
		//ofs.imbue(std::locale("Japanese", LC_CTYPE));
		ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs.open(path, std::ios::app);
		ofs << something.str() << std::endl;
		ofs.close();
	}

public:
	logger(const std::wstringstream& something)
	{
		const _TCHAR* path = _T("myapp.log");
		std::wofstream ofs;
		//ofs.imbue(std::locale("Japanese", LC_COLLATE));
		//ofs.imbue(std::locale("Japanese", LC_CTYPE));
		ofs.imbue({ {}, new std::codecvt_utf8<wchar_t, 0x10FFFF> });
		ofs.open(path, std::ios::app);
		ofs << something.str() << std::endl;
		ofs.close();
	}
};

