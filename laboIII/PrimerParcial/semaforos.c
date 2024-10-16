#include "semaforos.h"
#include <sys/sem.h>
#include "clave.h"
#include <sys/ipc.h>
#include "stdlib.h"
#include "stdio.h"

#define KEY 12

int creo_semaforo()
{
	key_t clave = creoClave(KEY);
	int idSemaforo = semget(clave, 1, 0600|IPC_CREAT);
	
	if(idSemaforo == -1)
	{
		return 0;
	}	
	
	return idSemaforo;
}

void inicia_semaforo(int idSemaforo, int valor) 
{
	semctl(idSemaforo, 0, SETVAL, valor);
}

void levanta_semaforo(int idSemaforo) 
{
	struct sembuf operacion;
	operacion.sem_num = 0;
	operacion.sem_op = 1;
	operacion.sem_flg = 0;

	semop(idSemaforo, &operacion, 1);
}

void espera_semaforo(int idSemaforo) 
{
	struct sembuf operacion;
	operacion.sem_num = 0;
	operacion.sem_op = -1;
	operacion.sem_flg = 0;

	semop(idSemaforo, &operacion, 1);
}


