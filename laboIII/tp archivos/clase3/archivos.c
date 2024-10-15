#include "archivos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int STR_LEN = 100;

void readFile(char filename[]){
	FILE* file;
	char line[100];
	
	file = openFile(filename, "r");
	if(file != 0) 
	{
		memset(line, 0x00, STR_LEN);
		while(!feof(file))
		{
			fscanf(file, "%s \n", line);
			printf("%s \n", line);
		}

		closeFile(file);
	}
} 

void writeFile(char filename[], int productValue){
	FILE* file = openFile(filename, "a");


	if(file != 0) 
	{
		fprintf(file, "PRODUCTO-%02d\n", productValue);
		closeFile(file);
	}
	
}

FILE *openFile(char filename[], char mode[]){
	FILE* file = fopen(filename, mode);

	if(file == NULL)
	{
		return 0;
	}

	return file;
}

void closeFile(FILE *file)
{
	fclose(file);
}

char* getLastLine(char filename[])
{
	char line[100];
	FILE* file = openFile(filename, "r");

	while(!feof(file))
	{	
		fgets(line, STR_LEN, file);
	}

	return (char*)line;
}



