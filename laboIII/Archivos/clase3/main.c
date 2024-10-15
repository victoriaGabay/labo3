#include "stdio.h"
#include <stdlib.h>
#include <archivos.h>
#include "string.h"
#include <productor.h>
#include <consumidor.h>

int main (int incant, char *szarg[]){
	int option;
	char *filename = szarg[1];

	if(filename){
		
		printf("Ingrese 1 para producir o 2 para consumir");
		scanf("%d", &option);

		switch(option){
			case 1:
				producir(filename);
				break;
			case 2: 
				consumir(filename);
				break;
			default:
				printf("Opción no valida.");
		}			
	}
	else
	{
		printf("Nombre de archivo invalido \n");
	}
		
	return 0;
}
