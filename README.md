# Visual Studio でブレークポイントのかわりに(2020-03-31)

```cpp
__asm int 3
```

# メモリリーク検出 - Valgrind at Ubuntu 18.04 LTS (2020-04-04)

Valgrind http://www.valgrind.org/downloads/current.html

```
tar xvf valgrind-3.15.0.tar.bz2
cd valgrind-3.15.0
./configure
make
sudo make install
```

To detect.

```
valgrind --leak-check=yes ./your-application arg1 arg2
```

To uninstall

```
make uninstall

find /usr/local/include/valgrind/
rm -fr /usr/local/include/valgrind

find /usr/local/lib/valgrind/
rm -fr /usr/local/lib/valgrind
```

* デバッグオプションを付けて make すると、ソース位置も出力するようになります。

```
g++ main.cpp -o main -g
```

* ソース位置が正しく出力されない場合は、最適化もやめてみます。

```
g++ main.cpp -o main -O00 -g
```


# DLL で標準出力

```CPP
void CreateDllConsole()
{
#ifdef DEBUG
	setlocale(LC_ALL, "Japanese");
	_tsetlocale(LC_ALL, _T("Japanese"));

	AllocConsole();

	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
#endif
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	CreateDllConsole();
	...
}
```

# std::wcout は使うべからず

わすれた

# ICU - International Components for Unicode
* 日本語文字列の操作に困ったら行くところ
  http://site.icu-project.org

# warning C4566: ユニバーサル文字名 '\u00B5' によって表示されている文字は、現在のコード ページ (932) で表示できません (Microsoft Visual Studio 2015 Community, 2020-08-15)

1. ソースコードは UTF-8 with BOM で保管。

2. コンパイラの追加オプションに `/execution-charset:utf-8` または `/utf-8` を追加する。
    * Microsoft Visual Studio 2015 Community  
      → プロジェクトの設定  
      → 構成プロパティ  
      → C/C++  
      → コマンドライン  
      → 追加のオプション  
    * なお `/source-charset:utf-8` は効かなかった。

# 2020-09-10 shared_ptr、unique_ptr を扱う際の注意点
https://postd.cc/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
