// map.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <string>
#include <map>
#include <locale.h>

class container
{
public:
    std::wstring get(const wchar_t* key) const;
    void put(const wchar_t* key, const wchar_t* value);
private:
    std::map<std::wstring, std::wstring> _map;
};

std::wstring container::get(const wchar_t* key) const
{
    auto it = this->_map.find(key);
    if (it == this->_map.end()) return L"";
    return it->second;
}

void container::put(const wchar_t* key, const wchar_t* value)
{
    this->_map[key] = value;
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    _wsetlocale(LC_ALL, L"Japanese");

    {
        std::map<std::wstring, std::wstring> user;

        user[L"電話"] = L"80-090-1872-0918";

        const std::wstring email = user[L"メールアドレス"]; // ←要素が空で作成されます。
        const std::wstring address = user[L"住所"]; // ←要素が空で作成されます。
        const std::wstring phone = user[L"電話"];

        wprintf(L"email: [%s], phone: [%s], address: [%s]", email.c_str(), phone.c_str(), address.c_str());
    }

    {
        container c;

        c.put(L"電話", L"80-090-1872-0918");

        const std::wstring email = c.get(L"メールアドレス");
        const std::wstring address = c.get(L"住所");
        const std::wstring phone = c.get(L"電話");

        wprintf(L"email: [%s], phone: [%s], address: [%s]", email.c_str(), phone.c_str(), address.c_str());
    }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
