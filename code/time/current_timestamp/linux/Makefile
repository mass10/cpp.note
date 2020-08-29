HEADER_PATH=boost_1_65_1
app: ~main.o Makefile
	g++ ~main.o -o app -I$(HEADER_PATH)
~main.o: main.cpp Makefile
	g++ -c main.cpp -o ~main.o -I$(HEADER_PATH)
