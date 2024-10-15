#include "stdlib.h"
#include "stdio.h"
#include "semaforos.h"
#include "unistd.h"
#include "archivos.h"
#include "string.h"
#include "funciones.h"
#include "definiciones.h"

int main(int incant, char *szarg[])
{
	int idSemaforo = creo_semaforo();
	int panel = 0;
	char *filename;
	char mensaje[1000] = "default";
	char *line;

	if(szarg[1])
	{
		panel = atoi(szarg[1]);
	}

    	while (1)
    	{	
        	espera_semaforo(idSemaforo);

		filename = getFileName(panel);

		openFile(filename, "r");

		while(!isFeof())
		{
			line = readFile();

			if(strcmp(line, mensaje) != 0)
			{
				memset(mensaje, 0x00, sizeof(mensaje));
			 	memcpy(mensaje, line, strlen(line));
			}		
		}
		
		closeFile();

		printf("Mensaje: %s \n", mensaje);
		
		levanta_semaforo(idSemaforo);
		
		usleep(ESPERA);
	}
	return 0;
}
