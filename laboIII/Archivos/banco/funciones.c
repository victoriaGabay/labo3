#include "funciones.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "funciones.h"

int obtenerNumeroAleatorio(int desde, int hasta){

	return (rand()%(hasta-desde+1))+desde;
}

char *getFileName(int nroCajero)
{
	switch(nroCajero){
		case 1:
			return FILE_1; break;
		case 2:
			return FILE_2; break;
		case 3: 
			return FILE_3; break;	
	
	}
	return "";
}
