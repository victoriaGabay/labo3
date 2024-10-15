#include "stdlib.h"
#include "stdio.h"
#include "global.h"
#include "definiciones.h"
#include "colas.h"
#include "funciones.h"
#include "string.h"
#include "time.h"
#include "memoria.h"
#include <sys/shm.h>
#include "unistd.h"
#include "pthread.h"
#include "sys/ipc.h"

pthread_mutex_t mutex;
int idColaMensajes;


void tirarAlArco(jugador *j)
{
	int jugadorEquipo1 = 0, fueGol = 0;
	char mens[5];
	mensaje msg;
	
	if(!*j->alguienEstaPateando)
	{
		*j->alguienEstaPateando = 1;
		printf("Soy el jugador %d y voy a disparar al arco.\n", j->id);
		memset(mens, 0x00, sizeof(mens));
		sprintf(mens, "%d", j->tipo);
		enviarMensaje(idColaMensajes, MSG_JUG_EQUIPO_1, j->id, EVT_PATEA, mens);
		recibirMensaje(idColaMensajes, j->id, &msg, 0);
		if(msg.event == EVT_RESULTADO_TIRO)
		{
			sscanf(msg.msg, "%d", &fueGol);
			printf("Soy el jugador %d y metí gol. \n", j->id);
			*j->golesEquipo = *j->golesEquipo+1;			
		}
	}
}

void *handlePlayersThread(void *param)
{
	jugador *j = (jugador *)param;
	int jugadorEquipo1 = 0, fueGol = 0;
	int decidirSiFueGol = 0;	
	char mens[5];
	mensaje msg;

	printf("Jugador %d listo.\n", j->id);
	while(1)
	{
	printf("Jugador %d.\n", j->id);
		if(j->id == MSG_JUG_EQUIPO_2)
		{
			pthread_mutex_lock(&mutex);
			recibirMensaje(idColaMensajes, j->id, &msg, 0); 
			pthread_mutex_unlock(&mutex);

			if(msg.event == EVT_PATEA)
			{
				decidirSiFueGol = obtenerNumeroAleatorio(0, 1);
				sscanf(msg.msg, "%d", &jugadorEquipo1);
				if(decidirSiFueGol)
				{
					printf("El %s del equipo 1 metio gol. \n", getTipoJug(jugadorEquipo1));
				}
				else
				{
					printf("El tiro del %s equipo 1 fue fuera. \n", getTipoJug(jugadorEquipo1));
				}
				memset(mens, 0x00, sizeof(mens));
				sprintf(mens, "%d", decidirSiFueGol); 
				printf("Le voy a mandar mensaje a %d \n", j->id);
				
pthread_mutex_lock(&mutex);
				enviarMensaje(idColaMensajes, msg.rte, j->id, EVT_RESULTADO_TIRO, mens);

				*j->puedeTirar = 1;
				*j->alguienEstaPateando = 0;
			}
			
		}
		else
		{
			if(*j->puedeTirar)
			{
				tirarAlArco(j);
			}
			else
			{

			}
		}

		if(*j->golesEquipo >= 5)
		{
			break;
		}
		usleep(100);
	}
	pthread_exit((void *)"Listo");
}

int main(int incant, char *szarg[])
{
	int idMemoria, i, golesEquipo, puedeTirar = 0, alguienPateando = 0;
	datos *memoria= NULL;
	jugador *jugadores;
	pthread_t * idThread;
	pthread_attr_t atributos;
	golesEquipo = 0;
	memoria = (datos*)crearMemoria(sizeof(datos), &idMemoria, CLAVE_BASE);
	idColaMensajes = creoIdColaMensajes(CLAVE_BASE);
	borrarMensajes(idColaMensajes);
	memoria[0].equipo2Listo = 1;
	while(!memoria[0].equipo1Listo)
	{
		printf("Inicie al equipo 1 para poder comenzar \n");
		printf("Debido al retraso del equipo 1, el equipo 2 hara el primer saque.\n");
		memoria[0].primerEquipo = 2;
		puedeTirar = 1;	
		usleep(100);
	}

	idThread = (pthread_t *)malloc(sizeof(pthread_t)*5);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&mutex, NULL);
	jugadores = (jugador*)malloc(sizeof(jugador)*5);
	srand(time(NULL));

	for(i = 0; i < 5; i++)
	{	
		jugadores[i].id = MSG_JUG_EQUIPO_2 + i;
		jugadores[i].golesEquipo = &golesEquipo;
		jugadores[i].tipo = getTipo(i);
		jugadores[i].puedeTirar = &puedeTirar;
		jugadores[i].alguienEstaPateando = &alguienPateando;
		pthread_create(&idThread[i], &atributos, handlePlayersThread, &jugadores[i]);
	}
	
	for(i = 0; i < 5; i++)
	{	
		pthread_join(idThread[i], NULL);
	}
	
	
	pthread_mutex_destroy(&mutex);
	shmdt((char *)memoria);
	shmctl(idMemoria, IPC_RMID, (struct shmid_ds *)NULL);
}
