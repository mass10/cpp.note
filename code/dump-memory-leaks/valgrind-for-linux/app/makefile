main: .main.o .lib.o makefile
	g++ .main.o .lib.o -o main

.lib.o: lib.h lib.cpp makefile
	g++ -c lib.cpp -o .lib.o -g

.main.o: main.cpp makefile
	@# デバッグオプションあり
	g++ -c main.cpp -o .main.o -g
	@# ソース位置が正しく出力されない場合は最適化もやめる
	@#	g++ main.cpp -o .main.o -g -O00
