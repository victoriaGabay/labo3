#include "stdlib.h"
#include "stdio.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"
#include "definiciones.h"
#include "time.h"
#include "string.h"
#include "unistd.h"

int main(int incant, char *szarg[])
{
	int menu, precio, conPostre, idSemaforo;
	char *filename, *line, *charMenu;
	filename = (char*)malloc((LEN+1)*sizeof(char));
	line = (char*)malloc((LEN+1)*sizeof(char));
	charMenu = (char*)malloc((LEN+1)*sizeof(char));
	
	srand(time(NULL));
	idSemaforo = creo_semaforo();
	inicia_semaforo(idSemaforo, VERDE);

	while(1)
	{
		menu = obtenerNumeroAleatorio(1, 3);
		memset(filename, 0x00, sizeof(filename));
		memset(line, 0x00, sizeof(line));
		memset(charMenu, 0x00, sizeof(charMenu));
		strcpy(filename, getFileName(menu));

		precio = getMenuPrice(menu);
		
		printf("Quiere agregar postre al menu %d? Ingrese 1 por si o 0 por no: ", menu);
		scanf("%d",&conPostre);
		
		if(conPostre)
		{
			precio = precio + 200;
		} 
		
		strcpy(charMenu, getMenu(menu));
		sprintf(line, OUT_FORMAT, precio, conPostre, charMenu);

		espera_semaforo(idSemaforo);

		openFile(filename, "a");
		writeFile(line);
		closeFile();
		levanta_semaforo(idSemaforo);
		usleep(10000);
	}

	
	

		
	free(filename);
	free(line);
	return 0;
	
}
