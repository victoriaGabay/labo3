#include "stdio.h"
#include "stdlib.h"
#include "reader.h"
#include "archivos.h"
#include "string.h"
#include "funciones.h"
#include "definiciones.h"
#include "unistd.h"

int mostrarMensaje(int nroPanel)
{
	char *line;
	char *filename;
	
	line = (char*)malloc((LEN+1)*sizeof(char));
	memset(line, 0x00, sizeof(line));
	filename = (char*)malloc((LEN+1)*sizeof(char));
	memset(filename, 0x00, sizeof(filename));

	strcpy(filename, getFileName(nroPanel);	

	if(!openFile(filename, "r")){
		return 0;
	}
	while(!isFeof())
	{
		line = readFile();
		printf("Mensaje del panel %d: %s \n", nroPanel, line);
	}

	free(line);

	return 1;
}


