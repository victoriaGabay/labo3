#ifndef _ARCHIVOS
#define _ARCHIVOS

#include "stdio.h"

void readFile(char filename[]);
void writeFile(char filename[], int productValue);
FILE *openFile(char filename[], char mode[]);
void closeFile(FILE *file);
char* getLastLine(char filename[]);

#endif
