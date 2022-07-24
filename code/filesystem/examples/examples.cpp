// examples.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

void rtrim(_TCHAR* line);
string get_last_error_message(DWORD error);
void report_last_error(DWORD error);
void report_last_error();

/// <summary>
/// エラー error を診断します。
/// </summary>
/// <param name="error"></param>
/// <returns>エラーメッセージ</returns>
string get_last_error_message(DWORD error) {
	_TCHAR text[2000] = _T("");
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT,
										text, sizeof(text) / sizeof(_TCHAR), NULL);
	rtrim(text);
	return text;
}

/// <summary>
/// エラー error を診断します。
/// </summary>
/// <param name="error">GetLastError が返したエラー番号</param>
void report_last_error(DWORD error) {
	if (error == 0)
		return;
	const string message = get_last_error_message(error);
	_tprintf(_T("[ERROR] %s(error: %d)\n"), message.c_str(), error);
}

/// <summary>
/// 最後に発生したエラーを診断します。
/// </summary>
void report_last_error() {
	const DWORD error = GetLastError();
	if (error == 0)
		return;
	const string message = get_last_error_message(error);
	_tprintf(_T("[ERROR] %s(error: %d)\n"), message.c_str(), error);
}

/// <summary>
/// 右端トリム
/// </summary>
/// <param name="line">文字列バッファ</param>
void rtrim(_TCHAR* line) {
	_TCHAR* pos = line;

	while (*pos != 0x00)
		pos++;

	while (line <= pos)
	{
		switch (*pos)
		{
		case 0x00:
			break;
		case L' ':
		case L'\t':
		case L'\r':
		case L'\n':
			*pos = 0x00;
			break;
		default:
			return;
		}
		pos--;
	}
}

bool touch(const _TCHAR* path)
{
	FILE* file = NULL;
	_tfopen_s(&file, path, _T("w+"));
	if (file == NULL)
		return false;
	fprintf(file, "hello!\n");
	fclose(file);
	return true;
}

/// <summary>
/// ファイルシステムの評価
/// </summary>
void diagnose_filesystem() {
	const _TCHAR* const path = _T("C:\\tmp\\symlinc");

	WIN32_FILE_ATTRIBUTE_DATA data = {};
	_GET_FILEEX_INFO_LEVELS required_level = _GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard;
	if (!GetFileAttributesEx(path, required_level, &data)) {
		report_last_error();
		return;
	}

	if (data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		_tprintf(_T("[DEBUG] Archive\n"));
	if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		_tprintf(_T("[DEBUG] Directory\n"));
	if (data.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		_tprintf(_T("[DEBUG] Read-Only\n"));
	if (data.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
		_tprintf(_T("[DEBUG] reparse point or a symbolic link\n"));

	WIN32_FIND_DATA data2 = {};
	if (!FindFirstFile(path, &data2)) {
		report_last_error();
		return;
	}

	// data2.dwReserved0 に reparse point tag が入る？？？

	// 失敗
	// struct _stat s = {};
	// int result = _tstat(path, &s);
}

/// <summary>
/// エントリーポイントです。
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[]) {

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_tsetlocale(LC_ALL, _T("Japanese"));

	// ファイルシステムの評価
	diagnose_filesystem();

	return 0;
}
