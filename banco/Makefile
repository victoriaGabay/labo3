CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : clean cajero tesorero

cajero : clave.h semaforos.h archivos.h funciones.h definiciones.h
	$(CC) -o cajero cajero.c clave.c semaforos.c archivos.c funciones.c $(CFLAGS) $(HEADERS)
tesorero : clave.h semaforos.h archivos.h funciones.h definiciones.h
	$(CC) -o tesorero tesorero.c clave.c semaforos.c archivos.c funciones.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o cajero tesorero

