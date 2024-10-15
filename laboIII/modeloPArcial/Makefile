CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : clean control panel

control : semaforos.h archivos.h clave.h definiciones.h sender.h funciones.h reader.h
	$(CC) -o control cci.c semaforos.c archivos.c clave.c sender.c reader.c funciones.c $(CFLAGS) $(HEADERS)

panel: semaforos.h archivos.h clave.h definiciones.h funciones.h
	$(CC) -o panel panel.c semaforos.c archivos.c clave.c funciones.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o control
	rm -rf *o panel

