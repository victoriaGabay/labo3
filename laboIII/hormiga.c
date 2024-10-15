#include "stdlib.h"
#include "stdio.h"
#include "memoria.h"
#include "definiciones.h"
#include "global.h"
#include "time.h"
#include "colas.h"
#include "pthread.h"
#include "unistd.h"
#include <sys/shm.h>
#include "string.h"
#include "funciones.h"

pthread_mutex_t mutex;
typedef struct Data data;
int idColaMensajes;

void *handleAntThread(void *param)
{
	hormiga *h = (hormiga *)param;
	mensaje msg;
	char tipo[100], respuesta[4];
	int insumo = 0, cantidad;
	
	while(1)
	{
		pthread_mutex_lock(&mutex);
		memset(tipo, 0x00, sizeof(tipo));
		recibirMensaje(idColaMensajes, h->id, &msg);
		sscanf(msg.msg, "%d", &insumo);

		if(h->cantPalitos > TARGET || h->cantHojas > TARGET || h->cantComida > TARGET || h->cantPiedras > TARGET)
		{
			printf("La hormiga %d ha terminado su trabajo. \n", h->id);
			enviarMensaje(idColaMensajes, MSG_REINA, h->id, EVT_FIN_PARTICULAR, ""); 
			pthread_mutex_unlock(&mutex);
			break;
		}
		else
		{
	
			cantidad = obtenerNumeroAleatorio(DESDE, HASTA);
			strcpy(tipo, getInsumo(insumo));
			printf("La hormiga %d recolecto %d %s\n",h->id, cantidad, tipo);
			memset(respuesta, 0x00, sizeof(respuesta));
			sprintf(respuesta, "%d", cantidad);
			enviarMensaje(idColaMensajes, MSG_REINA, h->id, EVT_CONTINUO, respuesta);
			switch(insumo){
				case Palitos:
					 h->cantPalitos = h->cantPalitos+cantidad; 
					printf("La hormiga %d recolecto en total %d %s\n",h->id, h->cantPalitos, tipo);
					break;
				case Piedras:
					 h->cantPiedras = h->cantPiedras+cantidad;
					printf("La hormiga %d recolecto en total %d %s\n",h->id, h->cantPiedras, tipo); 
					break;
				case Hojas: 
					 h->cantHojas = h->cantHojas+cantidad; 
					printf("La hormiga %d recolecto en total %d %s\n",h->id, h->cantHojas, tipo); 
					break;	
				case Comida: 
					 h->cantComida = h->cantComida+cantidad; 
					printf("La hormiga %d recolecto en total %d %s\n",h->id, h->cantComida, tipo); 
					break;	
			}	
		}

		pthread_mutex_unlock(&mutex);
		usleep(10000);
	}
	

	pthread_exit((void *)"Listo");
}

int main(int incant, char *szarg[])
{
	int idMemoria, i;
	int cantHormigas = 0;
	data *memoria = NULL;
	hormiga *hormigas;
	pthread_t * idThread;
	pthread_attr_t atributos;

	idColaMensajes = creoIdColaMensajes(CLAVE_BASE);
	memoria = (data*)crearMemoria(sizeof(data), &idMemoria, CLAVE_BASE);
	cantHormigas = 0;
	
	if(szarg[1])
	{
		cantHormigas = atoi(szarg[1]);
	}

	if(!memoria[0].ingresado && cantHormigas > 0)
	{
		memoria[0].cantidadHormigas = cantHormigas;
		memoria[0].ingresado = 1;
	}
	else if(memoria[0].ingresado)
		cantHormigas = memoria[0].cantidadHormigas;
	}
		
	hormigas = (hormiga*)malloc(sizeof(hormiga)*cantHormigas);
	
	idThread = (pthread_t *) malloc(sizeof(pthread_t)*cantHormigas);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&mutex, NULL);
	
	srand(time(NULL));
	for(i = 0; i < cantHormigas; i++)
	{
		hormigas[i].id = MSG_OBRERA+i;
		hormigas[i].cantPalitos = 0;
		hormigas[i].cantHojas = 0;
		hormigas[i].cantComida = 0;
		hormigas[i].cantPiedras = 0;
		pthread_create(&idThread[i], &atributos, handleAntThread, &hormigas[i]);
	}
	
	for(i = 0; i < cantHormigas; i++)
	{	
		pthread_join(idThread[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	enviarMensaje(idColaMensajes, MSG_REINA, MSG_OBRERA, EVT_FIN, ""); 

	shmdt((char *)memoria);
	shmctl(idMemoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
