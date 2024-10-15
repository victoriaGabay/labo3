CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : clean control nuevo

control : clave.h semaforos.h archivos.h funciones.h definiciones.h
	$(CC) -o control controlMenu.c clave.c semaforos.c archivos.c funciones.c $(CFLAGS)    $(HEADERS)

nuevo : clave.h semaforos.h archivos.h funciones.h definiciones.h
	$(CC) -o nuevo nuevo.c clave.c semaforos.c archivos.c funciones.c $(CFLAGS) $(HEADERS)
clean: 
	rm -rf *o control nuevo

