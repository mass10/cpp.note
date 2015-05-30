### Makefile

XTENT=~

INCLUDE_FILES=-I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include

# *****************************************************************************
# default
# *****************************************************************************
main.app: ${XTENT}main.o 
	gcc ${XTENT}main.o $(pkg-config --cflags --libs glib-2.0) -o main.app -lglib-2.0

${XTENT}main.o: main.c Makefile
	gcc -Wall -o ${XTENT}main.o $(pkg-config --cflags --libs glib-2.0) -c main.c ${INCLUDE_FILES}

# *****************************************************************************
# clean
# *****************************************************************************
clean:
	rm -f ${XTENT}*.o *.app
