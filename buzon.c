//Enunciado:
//Un padre crea 5 hijos, lo hijos nada más crearse imprimen por pantalla un mensaje, los hijos después del mensaje se duermen, pasados 4 segundos en el programa padre, se despiertan todos los hijos y los hijos envian un mensaje de que se han despertado
//Notas: Emplear semáforos
//Un usuario puede pulsar CTRL + C, hay que capturar la señal y despertar todos los hijos, el último en morir debe ser el padre
//Hay que poner un semáforo en los hijos porque el padre debe ser el que espere 4 segundos
//Pasados 4 segundos el padre debe poner el semáforo a >=5 para que sigan los procesos

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <wait.h>

struct tipo_mensaje{
long tipo;
int info;
};

int main(){

int i;
int buzon;
struct tipo_mensaje mensaje;

if(buzon=msgget(IPC_PRIVATE,IPC_CREAT | 0600)==-1){
perror("Error en la creacion del buzon\n");
return -1;
}

printf("Soy el padre con PID:%d\n",getpid());

for(i=0;i<10;i++){
	
	switch (fork()){
	case 0:
	printf("Soy el hijo %d\n",i+1);
	if(msgrcv(buzon,&mensaje,sizeof(struct tipo_mensaje)-sizeof(long),i+1,MSG_NOERROR)==-1){
	perror("Error al recibir el mensaje\n");
	return -1;
	}
	printf("%d: He recibido %d y voy a morirme\n",i+1,mensaje.info);
	return 0;
	case -1:
	perror("Error en fork()");
	return -1;
	default:
        break;
        }
}

	sleep(1);
	for(i=0;i<10;i++){
	mensaje.tipo=i+1;
	mensaje.info=(i+1)*(i+1);
	
	
	if(msgsnd(buzon,&mensaje,sizeof(struct tipo_mensaje)-sizeof(long),MSG_NOERROR)==-1){
	perror("Error al enviar un mensaje\n");
	return -1;
        }
        }

        for(i=0;i<10;i++){
        wait(NULL);
        }
        
        printf("Soy el padre y voy a morirme\n");
return 0;
}

