#include "stdio.h"
#include "stdlib.h"
#include "semaforos.h"
#include "sender.h"
#include "definiciones.h"
#include "reader.h"
#include "unistd.h"
#include "string.h"

int main(int incant, char *szarg[])
{
	int option = 0, sucess = 0, nroPanel = 0;
	char *mensaje;
	int idSemaforo = creo_semaforo();
	inicia_semaforo(idSemaforo, VERDE);

	while(1)
	{
		printf("Ingrese 1 para Leer panel o 2 para escribir panel");
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Ingrese el numero de panel: ");
				scanf("%d", &nroPanel);
				
				espera_semaforo(idSemaforo);
				sucess = mostrarMensaje(nroPanel);
				if(!sucess) {
					printf("Hubo un problema al acceder al archivo");
				}
				levanta_semaforo(idSemaforo);

				break;
			case 2: 
				nroPanel = 0;

				mensaje = (char*)malloc(LEN*sizeof(char));
				memset(mensaje, 0x00, sizeof(mensaje));

				printf("\n Ingrese el mensaje de panel: ");
				scanf("%s", mensaje);
				
				printf("Ingrese el numero de panel: ");
				scanf("%d", &nroPanel);

				espera_semaforo(idSemaforo);

				mandarMensaje(nroPanel, mensaje);

				levanta_semaforo(idSemaforo);
				break;			
		}

		usleep(10);
	}

	free(mensaje);
	return 0;
}
