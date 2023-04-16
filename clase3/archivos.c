#include "archivos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define LEN 100

FILE *file;

char* readFile(){
	char line[LEN + 1];
	
	if(file != NULL) 
	{
		memset(line, 0x00, LEN);
		fscanf(file, "%s \n", line);
	}

	return line;

} 

void writeFile(char *line){
	if(file != NULL) 
	{
		fputs(line, file);
	}	
}

void openFile(char filename[], char mode[]){
	file = fopen(filename, mode);
}

void closeFile()
{
	fclose(file);
}

char* getLastLine()
{
	char line[LEN + 1];
	if(file != NULL)
	{
		while(!feof(file))
		{
			fgets(line, LEN, file);
		}
	}
	else
	{
		printf("Archivo nulo \n");
	}
	
	return line;
}

int isFeof()
{
	return feof(file);
}



