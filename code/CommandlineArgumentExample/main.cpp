// CommandlineArgumentExample.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <Windows.h>
#include <oleauto.h>

std::string read_file(const _TCHAR* path)
{
	std::string content;
	FILE* const file = _tfopen(path, _T("rb"));
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

std::wstring sjis2utf8(const char* src)
{
	const int ENC_TYPE = CP_UTF8; /* UTF-8 へ変換するとしたら何バイト必要なのか？を得る */
	// const int ENC_TYPE = CP_ACP;

	char spacer0[1] = "";
	_ASSERT(spacer0[0] == 0x00);

	const size_t original_length = strlen(src);

	// Unicode　文字列に変換するために必要なバッファのサイズを計算してもらう(0x00 含む +1 が返されます)
	const unsigned int required_size_of_new_buffer = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	_tprintf(_T("[TRACE] Required size of new buffer in bytes: [%d]\n"), required_size_of_new_buffer);
	_ASSERT(required_size_of_new_buffer != 0);

	// 新しいバッファを確保
	char spacer1[1] = "";
	_ASSERT(spacer1[0] == 0x00);

	wchar_t* new_buffer = new wchar_t[required_size_of_new_buffer];
	memset(new_buffer, 0x00, required_size_of_new_buffer * sizeof(wchar_t));

	char spacer2[1] = "";
	_ASSERT(spacer2[0] == 0x00);

	// 変換
	const int result = MultiByteToWideChar(
		CP_UTF8,
		0,
		src, // Pointer to the character string to convert.
		strlen(src), // Size, in bytes, of the string indicated by the lpMultiByteStr parameter
		new_buffer, // Pointer to a buffer that receives the converted string.
		required_size_of_new_buffer// Size, in characters
	);

	_tprintf(_T("[TRACE] Affected length in characters: [%d]\n"), result);

	std::wstring new_name = new_buffer;
	delete(new_buffer);

	_tprintf(_T("[TRACE] 変換結果: ["));
	_tprintf(new_name.c_str());
	_tprintf(_T("]\n"));

	return new_name.c_str();
}

// ファイル出力
void save_file(const _TCHAR* path, const wchar_t* content)
{
	FILE* file = _tfopen(path, _T("wb"));
	if (file == NULL)
	{
		return;
	}
	const size_t content_length = wcslen(content) * sizeof(wchar_t);
	_tprintf(_T("[TRACE] content length is [%zu]\n"), content_length);
	fwrite(content, content_length, 1, file);
	fclose(file);
}

// 正しい変換処理
void valid_conversion()
{
	std::string content = read_file(_T("C:\\Users\\irisa\\workspace\\cpp.note\\code\\CommandlineArgumentExample\\DATA.txt"));

	// 元の文字列
	printf("[TRACE] SOURCE [%s]\n", content.c_str());

	std::wstring new_name = sjis2utf8(content.c_str());

	_tprintf(_T("[TRACE] RESULT [%s]\n"), new_name.c_str());

//	new_name = _T("Apples Inc.");
//	new_name = _T("リンゴ株式会社");

	// wchar_t をバイナリで出力すると UTF-16LE になって出力される。
	save_file(_T("C:\\Users\\irisa\\workspace\\cpp.note\\code\\CommandlineArgumentExample\\OUT.log"), new_name.c_str());
}

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 標準出力にのみ影響、処理結果に影響しない
	_tsetlocale(LC_ALL, _T("Japanese.UTF-8"));

	_tprintf(_T("[TRACE] ### UTF-8 バイト配列 → UTF-8 wchar_t に変換するテスト 開始 ###\n"));

	valid_conversion();

	_tprintf(_T("[TRACE] --- 終了 ---\n"));
	
	return 0;
}
