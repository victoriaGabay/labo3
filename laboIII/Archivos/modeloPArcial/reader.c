#include "stdio.h"
#include "stdlib.h"
#include "reader.h"
#include "archivos.h"
#include "string.h"
#include "funciones.h"

void mostrarMensaje(int nroPanel)
{
	char *line;
	char *filename = getFileName(nroPanel);

	openFile(filename, "r");
	while(!isFeof())
	{
		line = readFile();
		printf("Mensaje del panel %d: %s \n", nroPanel, line);
	}
}


