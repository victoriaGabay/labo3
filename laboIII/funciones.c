#include <funciones.h>
#include "time.h"
#include<stdio.h>
#include<stdlib.h>

int obtenerNumeroAleatorio(int desde, int hasta){

	return (rand()%(hasta-desde+1))+desde;
}
