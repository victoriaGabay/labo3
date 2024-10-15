CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : tst

tst : archivos.h 
	$(CC) -o tst1 main.c archivos.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o tst1

