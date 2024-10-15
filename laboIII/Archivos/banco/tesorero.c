#include "archivos.h"
#include "funciones.h"
#include "definiciones.h"
#include "time.h"
#include "string.h"
#include "unistd.h"
#include "semaforos.h"
#include "stdio.h"
#include "stdlib.h"

int main(int incant, char *szarg[])
{
	int depositosEfec[4] = {0};
	int totalDepositosEfect[4] = {0};

	int depositosCheque[4] = {0};
	int totalDepositosCheque[4] = {0};

	char *filename, *line;
	char newFileName[15+1];
	int deposito, pago, cajero, i, cajeroExiste = 0;
	int idSemaforo = creo_semaforo();

	inicia_semaforo(idSemaforo, VERDE);

	while(1)
	{

		for(cajero = 0; cajero < 3; cajero++)
		{
			espera_semaforo(idSemaforo);
			filename = getFileName(cajero+1);
			openFile(filename, "r+");

			while(!isFeof())
			{
				cajeroExiste = 1;
				line = readFile();

				deposito = 0;
				pago = 0;
				sscanf(line, OUT_FORMAT, &deposito, &pago);

				if(pago == 1)
				{
					depositosEfec[cajero] = depositosEfec[cajero] + 1;
					totalDepositosEfect[cajero] = totalDepositosEfect[cajero] + deposito;
				}
				else
				{
					depositosCheque[cajero] = depositosCheque[cajero] + 1;
					totalDepositosCheque[cajero] = totalDepositosCheque[cajero] + deposito;
				}

			}
			
			if(cajeroExiste) {			
				depositosEfec[3] = depositosEfec[3] + depositosEfec[cajero];
				totalDepositosEfect[3] = totalDepositosEfect[3] + totalDepositosEfect[cajero];
				depositosCheque[3] = depositosCheque[3] + depositosCheque[cajero];
				totalDepositosCheque[3] = totalDepositosCheque[3] + totalDepositosCheque[cajero];
				memset(newFileName, 0x00, sizeof(newFileName));
				sprintf(newFileName, RENAMED_FILE, cajero+1, cajero);
				renameFile(filename, newFileName);
				cajeroExiste = 0;
			}
			closeFile();
			levanta_semaforo(idSemaforo);
		}
	
		printf("TOTAL \n");
		printf("TC-EFEC		T$-EFEC		TC-CHECK	T$-CHEQ \n");
		printf("%d		%d		%d		%d \n", depositosEfec[3], 			totalDepositosEfect[3], depositosCheque[3], totalDepositosCheque[3]);
		printf("\n");
		for(i = 0; i < 3; i++)
		{
			printf("CAJERO%d \n",i+1);
			printf("TC-EFEC		T$-EFEC		TC-CHECK	T$-CHEQ \n");
			printf("%d		%d		%d		%d \n", depositosEfec[i], totalDepositosEfect[i], depositosCheque[i], totalDepositosCheque[i]);	
			printf("\n");
		}

		usleep(5000);
	}

	return 0;
}
