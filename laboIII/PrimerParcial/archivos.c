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
		memset(line, 0x00, sizeof(line));
		fgets(line, sizeof(line), file);
	}

	return line;

} 

void writeFile(char line[]){

	if(file != NULL) 
	{
		fprintf(file, line);
	}	
}

int openFile(char filename[], char mode[]){
	return (file = fopen(filename, mode)) != 0;
}

void closeFile()
{

	if(file != NULL) {
	fclose(file);}
}

char* getLastLine()
{
	char line[LEN + 1];
	memset(line, 0x00, sizeof(line));

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



