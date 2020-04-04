// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "../MyClassLibrary1/MyClassLibrary1.h"

void test_hello()
{
    std::string hello = abcde1::hello();
    printf("[TRACE] hello: [%s]\n", hello.c_str());
}

void test_trim()
{
    std::string s = abcde1::MyUtilClass1::trim("     \r\n\tHello! \t\r\n        ");
    printf("[TRACE] trim: [%s]\n", s.c_str());
}

int main()
{
    test_hello();
    test_trim();
    return 0;
}
