#include "archivos.h"
#include "stdio.h"
#include "stdlib.h"

void readFile(char filename[]){
	FILE* file;
	char ch;

	file = fopen("tst.txt", "r");
	
	do 
	{
		ch = fgetc(file);
		printf("%c", ch);
	}
	while (ch != EOF );
	
	fclose(file);

} 

void writeFile(char newLine[]){
	FILE* file;

	file = fopen("tst.txt", "w");
	fprintf(file, newLine, 2);
	fclose(file);
}





