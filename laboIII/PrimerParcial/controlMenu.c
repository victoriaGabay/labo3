#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "definiciones.h"
#include "funciones.h"
#include "unistd.h"
#include "semaforos.h"

int main(int incant, char *szarg[])
{
	char *filename, *line, *tipoMenuChar;
	int tipoMenu, precio, tienePostre, idSemaforo;

	idSemaforo = creo_semaforo();
	if(szarg[1])
	{

		tipoMenu = getMenuType(szarg[1]);
		
		if(tipoMenu == 0)
		{
			printf("El tipo de menu no es valido \n");
			return 0;
		}

		filename = (char*)malloc((LEN+1)*sizeof(char));
		memset(filename, 0x00, sizeof(filename));
		strcpy(filename, getFileName(tipoMenu));

		line = (char*)malloc((LEN+1)*sizeof(char));
		tipoMenuChar = (char*)malloc((LEN+1)*sizeof(char));

		while(1)
		{
			espera_semaforo(idSemaforo);
			memset(line, 0x00, sizeof(line));
			openFile(filename, "r");
			while(!isFeof())
			{
				strcpy(line, readFile());
				if(strcmp("", line) != 0)
				{
					sscanf(line, OUT_FORMAT, &precio, &tienePostre, tipoMenuChar);
					printf("Menu: %s, Precio: %d, Incluye Postre %d \n", 						tipoMenuChar, precio, tienePostre);
					memset(tipoMenuChar, 0x00, sizeof(tipoMenuChar));
				}
			}
			if(strcmp("", line) == 0)
			{
				printf("~~~~ FIN ARCHIVO ~~~~  \n");
			}
			closeFile();
			levanta_semaforo(idSemaforo);
			usleep(ESPERA*10000);
		}	
	}
	else
	{
		printf("Se debe ingresar el tipo de menu a controla");
	}

	free(filename);
	free(line);
	free(tipoMenuChar);

	return 0;

}
