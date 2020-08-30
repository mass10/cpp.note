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

wchar_t* alloc_sys_string(const char* source)
{
	// CP_UTF8 配列を wchar_t に詰め替えるために必要な wchar_t バッファの長さ(0x00 含む)
	const unsigned int requiredSizeOfBuffer = MultiByteToWideChar(CP_UTF8, 0, source, -1, NULL, 0);
	wchar_t* buffer = SysAllocStringLen(NULL, requiredSizeOfBuffer);
	memset(buffer, 0x00, requiredSizeOfBuffer * sizeof(wchar_t));
	const int result = MultiByteToWideChar(CP_UTF8, 0, source, strlen(source), buffer, requiredSizeOfBuffer);
	return buffer;
}

// UTF-8 のバイト配列を、wchar_t 配列に変換します。wchar_t の内部構造は UTF-16 LE となります。
std::wstring utf8_to_wchar(const char* src)
{
	const int ENC_TYPE = CP_UTF8;

	const unsigned int required_size_of_new_buffer = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	_tprintf(_T("[TRACE] Required size of new buffer in bytes: [%d]\n"), required_size_of_new_buffer);

	wchar_t* new_buffer = new wchar_t[required_size_of_new_buffer];

	// 変換
	const int result = MultiByteToWideChar(CP_UTF8, 0, src, -1, new_buffer, required_size_of_new_buffer);
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

void test_convert_file()
{
	// UTF-8 のバイト配列。デバッガでは目視できません。
	const std::string content = read_file(_T("data-in.txt"));
	printf("[TRACE] SOURCE [%s]\n", content.c_str());

	// wchar_t 配列に変換します。
	if (false)
	{
		BSTR buffer2 = alloc_sys_string(content.c_str());
		create_file(_T("data-out.txt"), buffer2);
		SysFreeString(buffer2);
	}
	else
	{
		std::wstring new_name = utf8_to_wchar(content.c_str());
		_tprintf(_T("[TRACE] RESULT [%s]\n"), new_name.c_str());

		// ファイルに保存します。
		create_file(_T("data-out.txt"), new_name.c_str());
	}

}

void dump_letter(wchar_t letter)
{
	_tprintf(_T("0x%04X"), letter);
}

void test_allocation_buffer(int size)
{
	BSTR buffer = SysAllocStringLen(NULL, size);
	// 全てのバイトが 0x00 になっていることの確認
	printf("[TRACE] %u CHARACTER(S) ALLOCATED: [", size);
	for (int i = 0; i < size; i++)
	{
		if (i != 0) printf(",");
		const wchar_t& letter = buffer[i];
		dump_letter(letter);
	}
	SysFreeString(buffer);
	printf("]\n");
}

void test_allocation_buffer_2(int size)
{
	wchar_t* buffer = new wchar_t[size];
	// 全てのバイトが 0x00 になっていることの確認
	printf("[TRACE] %u CHARACTER(S) ALLOCATED: [", size);
	for (int i = 0; i < size; i++)
	{
		if (i != 0) printf(",");
		const wchar_t& letter = buffer[i];
		dump_letter(letter);
	}
	delete[] buffer;
	printf("]\n");
}

// バッファ確保時の初期状態を知る
void test_allocating_buffer()
{
	printf("\n");

	_tprintf(_T("[TRACE] $$$ テスト 1 (SysAllocStringLen) $$$\n"));

	printf("\n");
	for (unsigned int i = 0; i < 10; i++)
	{
		const int random_size = 1 + rand() % 9;
		test_allocation_buffer(random_size);
	}
	printf("\n");

	_tprintf(_T("[TRACE] $$$ テスト 2 (new) $$$\n"));

	printf("\n");
	for (unsigned int i = 0; i < 10; i++)
	{
		const int random_size = 1 + rand() % 9;
		test_allocation_buffer_2(random_size);
	}

	printf("\n");
}

// エントリーポイント
int _tmain(int argc, _TCHAR* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 標準出力にのみ影響、処理結果に影響しない
	_tsetlocale(LC_ALL, _T("Japanese.UTF-8"));

	srand(GetTickCount());

	_tprintf(_T("[TRACE] ### UTF-8 バイト配列 → UTF-8 wchar_t に変換するテスト 開始 ###\n"));

	// ========== UTF-8 -> wchar_t への変換とファイル出力 ==========
	if (true)
		test_convert_file();

	// ========== バッファ確保時の初期状態を知る ==========
	if (false)
		test_allocating_buffer();

	_tprintf(_T("[TRACE] --- 終了 ---\n"));

	return 0;
}
