#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define LONGITUD_MAXIMA 100

int main (){

	int buzon, envio, recibo;

	struct tipo_mensaje{
		long tipo;
		char remite[12];
		char msg[LONGITUD_MAXIMA];
	} mensaje;

	buzon=msgget(IPC_PRIVATE, IPC_CREAT|0600);
	if (buzon==1){
		perror("No se puede crear el buzon");
		return 10;
	}

	switch(fork()){
		case -1: perror("fork");
		    	return 1;
	
		case 0:
		    	mensaje.tipo=2;
		    	sprintf(mensaje.remite, "%d", getpid());
		    
		    	printf("Soy el hijo, pulsa algo para que envie el mensaje \n");
		    	getchar();
		    
		    	sprintf(mensaje.msg, "Hola padre, te mando | : %d \n", rand());
		    
		    	envio=msgsnd(buzon, &mensaje, sizeof(struct tipo_mensaje)-sizeof(long),0);
		    
		    	if(envio==-1){
		    		perror("Fallo en  el envio");
		    		return 2;
		    	}
		    	break;
		    	
		default:
			mensaje.tipo=2;
			recibo=msgrcv(buzon, &mensaje, sizeof(struct tipo_mensaje) - sizeof(long), 				mensaje.tipo, MSG_NOERROR);
			
			if(recibo==-1){
				perror("Fallo en la recepcion");
				return 3;
			}
			printf("Soy el padre y mi hijo %s, me ha mandado %s \n", mensaje.remite, 				mensaje.msg);
		}
	//Borrar buzon
	return 0;
}
				  
		  
		    
		    
	
