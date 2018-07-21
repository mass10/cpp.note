PREFIX=.
hello.app: ${PREFIX}hello.o
	g++ ${PREFIX}hello.o -o hello.app -lpcap
${PREFIX}hello.o: hello.cpp
	g++ -c hello.cpp -o ${PREFIX}hello.o
