#include <crtdbg.h>
#include <tchar.h>
#include <iostream>

// 不明な型 T の連続したバッファ
template <class T>
class buffer
{
public:

    // コンストラクター
    buffer(size_t size) :
        _size(size), _buffer(new T[size])
    {
    }

    // デストラクター
    ~buffer()
    {
        delete _buffer;
    }

    // インデクサーの実装
    T operator[] (size_t pos)
    {
        if (this->_size <= pos)
            return NULL;
        return this->_buffer[pos];
    }

    // バッファの先頭アドレスへのキャスト
    operator T* ()
    {
        return this->_buffer;
    }

private:

    // サイズ
    const size_t _size;

    // バッファの先頭
    T* const _buffer;
};

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    _tsetlocale(LC_ALL, _T("Japanese"));

    // 安全なバッファの確保
    buffer<_TCHAR> s(100);
 
    // dest_size(第二引数)は文字数です。
    _tcscpy_s(s, 100 / sizeof(_TCHAR), _T("こんにちは！"));

    wprintf(_T("[%s]\n"), (wchar_t*)s);
}
