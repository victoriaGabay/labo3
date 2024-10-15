#ifndef _SEMAFOROS
#define _SEMAFOROS

int creo_semaforo();
void inicia_semaforo(int idSemaforo, int valor);
void levanta_semaforo(int idSemaforo);
void espera_semaforo(int idSemaforo);

#endif
