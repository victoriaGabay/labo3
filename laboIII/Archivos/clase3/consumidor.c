#include "archivos.h"
#include "stdio.h"
#include "stdlib.h"
#include "consumidor.h"

void consumir(char filename[]){
	char *line;
	openFile(filename, "r");
	
	while(!isFeof())
	{
		line = readFile();
		printf("%s \n", line);
	}
	
	
	closeFile();
}
