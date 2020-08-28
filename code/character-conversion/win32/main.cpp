// CommandlineArgumentExample.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <Windows.h>
#include <locale.h>
#include <oleauto.h>
#include <string>

std::string read_file(const _TCHAR* path)
{
	FILE* file = NULL;
	_tfopen_s(&file, path, _T("rb"));
	if (file == NULL)
		return "";

	std::string content;
	while (true)
	{
		char line[32 + 1] = "";
		const size_t read_size = fread(line, 32, 1, file);
		content.append(line);
		if (read_size == 0)
			break;
	}

	fclose(file);

	return content;
}

// UTF-8 のバイト配列を、wchar_t 配列に変換します。wchar_t の内部構造は UTF-16 LE となります。
std::wstring utf8_to_wchar(const char* src)
{
	const int ENC_TYPE = CP_UTF8;

	const unsigned int required_size_of_new_buffer = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	_tprintf(_T("[TRACE] Required size of new buffer in bytes: [%d]\n"), required_size_of_new_buffer);

	wchar_t* new_buffer = new wchar_t[required_size_of_new_buffer];
	memset(new_buffer, 0x00, required_size_of_new_buffer * sizeof(wchar_t));

	// 変換
	const int result = MultiByteToWideChar(
		CP_UTF8,
		0,
		src, // Pointer to the character string to convert.
		-1, // Size, in bytes, of the string indicated by the lpMultiByteStr parameter
		new_buffer, // Pointer to a buffer that receives the converted string.
		required_size_of_new_buffer// Size, in characters
	);

	_tprintf(_T("[TRACE] Affected length in characters: [%d]\n"), result);

	const std::wstring new_name = new_buffer;

	delete[] new_buffer;

	_tprintf(_T("[TRACE] 変換結果: ["));
	_tprintf(new_name.c_str());
	_tprintf(_T("]\n"));

	return new_name.c_str();
}

// ファイル出力
void create_file(const _TCHAR* path, const wchar_t* content)
{
	FILE* file = NULL;
	_tfopen_s(&file, path, _T("wb"));
	if (file == NULL)
		return;

	const size_t content_length = wcslen(content) * sizeof(wchar_t);
	_tprintf(_T("[TRACE] content length is [%zu]\n"), content_length);

	// wchar_t をバイナリで出力すると UTF-16LE のまま出力されます。
	fwrite(content, content_length, 1, file);

	fclose(file);
}

void convert_file()
{
	// UTF-8 のバイト配列。デバッガでは目視できません。
	const std::string content = read_file(_T("data-in.txt"));
	printf("[TRACE] SOURCE [%s]\n", content.c_str());

	// wchar_t 配列に変換します。
	std::wstring new_name = utf8_to_wchar(content.c_str());
	_tprintf(_T("[TRACE] RESULT [%s]\n"), new_name.c_str());

	// ファイルに保存します。
	create_file(_T("data-out.txt"), new_name.c_str());
}

// エントリーポイント
int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 標準出力にのみ影響、処理結果に影響しない
	_tsetlocale(LC_ALL, _T("Japanese.UTF-8"));

	_tprintf(_T("[TRACE] ### UTF-8 バイト配列 → UTF-8 wchar_t に変換するテスト 開始 ###\n"));

	convert_file();

	_tprintf(_T("[TRACE] --- 終了 ---\n"));

	return 0;
}
