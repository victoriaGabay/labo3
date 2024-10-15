#include "stdio.h"
#include<stdlib.h>
#include <archivos.h>
#include "string.h"

void consumir(char filename[]);
void producir(char filename[]);

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

void consumir(char filename[]){
	readFile(filename);
}

void producir(char filename[]){
	int i = 1;
	int lastNumberInt = 1;
	char* lastLine = getLastLine(filename);
	char lastNumber[4];


	memcpy(lastNumber, &lastLine[9], 4);
	lastNumberInt = atoi(lastNumber);
	
	for(i = lastNumberInt; i < (lastNumberInt + 10); i++)
	{
		writeFile(filename, i);
	}
}

