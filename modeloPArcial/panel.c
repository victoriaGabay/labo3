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
	char mensaje[LEN] = "default";
	char *filename;
	char *line;

	if(szarg[1])
	{
		panel = atoi(szarg[1]);
	}
	
	line = (char*)malloc((LEN+1)*sizeof(char));
	memset(line, 0x00, sizeof(line));
	filename = (char*)malloc((LEN+1)*sizeof(char));
	memset(filename, 0x00, sizeof(filename));
	strcpy(filename, getFileName(panel));

    	while (1)
    	{	
        	espera_semaforo(idSemaforo);

		while(openFile(filename, "r") == 0)
		{
			printf("No se pudo abrir el archivo \n");
			levanta_semaforo(idSemaforo);
			usleep(1000);
			espera_semaforo(idSemaforo);
		}

		while(!isFeof())
		{
			strcpy(line,readFile());

			if(strcmp(line, mensaje) != 0)
			{
			 	memcpy(mensaje, line, strlen(line));
			}		
		}
		
		closeFile();

		printf("Mensaje: %s \n", mensaje);
		
		levanta_semaforo(idSemaforo);
		
		usleep(ESPERA);
	}

	free(line);
	free(filename);
	return 0;
}
