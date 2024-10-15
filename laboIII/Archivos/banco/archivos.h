#ifndef _ARCHIVOS
#define _ARCHIVOS

#include "stdio.h"

char *readFile();
void writeFile(char *line);
void openFile(char filename[], char mode[]);
void closeFile();
char* getLastLine();
int isFeof();
void renameFile(char *oldName, char *newName);

#endif
