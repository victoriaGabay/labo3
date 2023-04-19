#include "stdio.h"
#include "stdlib.h"
#include "sender.h"
#include "archivos.h"
#include "string.h"
#include "funciones.h"
#include "definiciones.h"

void mandarMensaje(int nroPanel, char mensaje[])
{
	char *filename;
	char *line;
	int msgChanged = 0, sucess;	
	
	line = (char*)malloc((LEN+1)*sizeof(char));
	memset(line, 0x00, sizeof(line));
	filename = (char*)malloc((LEN+1)*sizeof(char));
	memset(filename, 0x00, sizeof(filename));
	strcpy(filename, getFileName(nroPanel));

	sucess = openFile(filename, "r");
	while(!isFeof()) {

		strcpy(line, readFile());
		msgChanged = strcmp(mensaje, line);			
	}

	closeFile();	

	if(msgChanged != 0)
	 {
		openFile(filename, "w");
		writeFile(mensaje);
		closeFile();
	}

	free(line);
	free(filename);
}


