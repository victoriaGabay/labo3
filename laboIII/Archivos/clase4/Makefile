CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : carga

carga : carga.c clave.h semaforos.h archivos.h carga.h
	$(CC) -o carga carga.c clave.c semaforos.c archivos.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o carga

