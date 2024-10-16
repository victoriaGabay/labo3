#include "funciones.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "funciones.h"
#include "string.h"

int obtenerNumeroAleatorio(int desde, int hasta){

	return (rand()%(hasta-desde+1))+desde;
}

char *getFileName(int menu)
{
	switch(menu){
		case 1:
			return FILE_1; break;
		case 2:
			return FILE_2; break;
		case 3: 
			return FILE_3; break;	
	
	}
	return "";
}

int getMenuType(char menu[])
{

	if(strcmp(menu, "A") == 0)
	{
		return 1;
	}
	else if(strcmp(menu, "B") == 0)
	{
		return 2;
	}
	else if(strcmp(menu, "C") == 0)
	{
		return 3;
	}

	return 0;
}

int getMenuPrice(int menu)
{
	switch(menu){
		case 1:
			return 1000; break;
		case 2:
			return 2000; break;
		case 3: 
			return 3000; break;	
	
	}
	return 0;
}

char *getMenu(int menu)
{
	switch(menu){
		case 1:
			return "A"; break;
		case 2:
			return "B"; break;
		case 3: 
			return "C"; break;	
	
	}
	return "";
}
