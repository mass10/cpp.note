#pragma once

#include <Windows.h>

// クリティカルセクションの生存期間を保証します。
class critical_section_lifetime
{
public:
	// コンストラクター
	critical_section_lifetime();
	// デストラクター
	~critical_section_lifetime();
private:
};

// クリティカルセクションの管理を提供する簡易的なクラスです。
class critical_section
{
	friend critical_section_lifetime;
public:
	// コンストラクター
	critical_section();
	// デストラクター
	~critical_section();
private:
	// クリティカルセクションの初期化
	// プロセス開始時に一度だけ実行する必要があります。
	static void init();
	// クリティカルセクションの破棄
	// プロセス終了時に一度だけ実行する必要があります。
	static void free();
	// クリティカルセクションの本体
	static CRITICAL_SECTION _section;
};
