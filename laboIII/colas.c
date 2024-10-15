#include "stdlib.h"
#include "stdio.h"
#include "colas.h"
#include "clave.h"
#include "definiciones.h"
#include "sys/ipc.h"
#include "sys/msg.h"
#include "string.h"

int creoIdColaMensajes(int clave)
{
	int id = msgget( creoClave(clave), 0600 | IPC_CREAT);
	
	if(id == -1)
	{
		printf("No se pudo obetener un id para la cola de mensajes \n");
		return 0;
	}
	
	return id;
}

int enviarMensaje(int idCola, long rDest, int rte, int evento, char* mesg)
{	

	int size;
	mensaje msg;
	printf("mensaje que recibo: %s \n", mesg);
	msg.dest = rDest;
	msg.rte = rte;
	msg.event = evento;
	strcpy(msg.msg, mesg);
	printf("mensaje que mando: %s \n", msg.msg);
	size = sizeof(msg.rte) + sizeof(msg.event) + sizeof(msg.msg); 
	return msgsnd(idCola, (struct msgbu *)&msg, size, IPC_NOWAIT);
}

int recibirMensaje(int idCola, long dest, mensaje *rMsg)
{
	mensaje msg;
	int res, size;

	res = msgrcv(idCola, (struct msgbu *)&msg, (sizeof(msg.rte) + sizeof(msg.event) + sizeof(msg.msg)), dest, IPC_NOWAIT);
	rMsg->dest = msg.dest;
	rMsg->rte = msg.rte;
	rMsg->event = msg.event;
	strcpy(rMsg->msg, msg.msg);
	
	return res;
}

int borrarMensajes(int idCola)
{
	mensaje msg;
	int res;
	
	do
	{
		res = msgrcv(idCola, (struct msgbu *)&msg, sizeof(msg.rte) + sizeof(msg.event) + sizeof(msg.msg), 0, IPC_NOWAIT);
	}
	while( res > 0);
	return res;
}

