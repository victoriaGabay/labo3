#ifndef _ARCHIVOS
#define _ARCHIVOS

#include "stdio.h"

char *readFile();
void writeFile(char *line);
int openFile(char filename[], char mode[]);
void closeFile();
char* getLastLine();
int isFeof();

#endif
