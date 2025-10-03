/*
Ejercicio
Un padre crea 2 hijos el primero de ellos genera un número aleatorio entre 0 y 9, cuando lo genera lo mete en memoria compartida y avisa al proceso p2, y  p2 cuando le avisan consulta en memoria compartida el número que ha generado p1 y lo imprime por pantalla 
El ejercicio del producto-consumidor

Sincronización de rendevouz

Memoria compartida
int shmget(key_t clave, size_t tamanNo, int shmflg);
int shmctl(int shmid,int cmd, struct shmid_ds *buf);
void *shmat(int shmid, void *shmaddr, int shmflg);
shmflg SHM_RDONLY, solo lectura
int shmdt(void *shmaddr); //destruir la referencia

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>


int main(){
int memoria;
int *numero;
int semaforo;
int i;

if((memoria=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0600))==-1) perror("shmget");

struct sembuf menos1;
menos1.sem_num=0;
menos1.sem_op=-1;
menos1.sem_flg=0;

struct sembuf mas1;
mas1.sem_num=0;
mas1.sem_op=1;
mas1.sem_flg=0;

struct sembuf menos2;
menos2.sem_num=1;
menos2.sem_op=-1;
menos2.sem_flg=0;

struct sembuf mas2;
mas2.sem_num=1;
mas2.sem_op=1;
mas2.sem_flg=0;

	if((semaforo=semget(IPC_PRIVATE,2,IPC_CREAT | 0600))==-1){
	perror("Error en la creacion del semáforo\n");
	return -1;
	}

	if(semctl(semaforo,0,SETVAL,1)==-1) {perror("semctl"); return -1;}
	if(semctl(semaforo,1,SETVAL,0)==-1) {perror("semctl"); return -1;}


switch (fork()){
case -1:
	perror("fork");
	return -1;
case 0:
	if((numero=shmat(memoria,NULL,SHM_RDONLY))==(void *)-1) perror("shmat");
	for(i=0;i<5;i++){
	if(semop(semaforo,&menos2,1)==-1) perror("semop");
	printf("El numero en memoria compartida es %d\n", *numero);
	if(semop(semaforo,&mas1,1)==-1) perror("semop");
	}
	if(shmdt(numero) == -1) perror("shmdt");
	return 0;
default:
	switch(fork()){
	case -1:
		perror("fork");
		return -1;
	case 0:
		if((numero=shmat(memoria,NULL,0))==(void *)-1) perror("shmat");
		srand(time(NULL));
		for(i=0;i<5;i++){
		if(semop(semaforo,&menos1,1)==-1) perror("semop");
		*numero=rand()%10;
		if(semop(semaforo,&mas2,1)==-1) perror("semop");
		}
		if(shmdt(numero) == -1) perror("shmdt"); 
		return 0;
	default:
		wait(NULL);
		wait(NULL);
		if(semctl(semaforo,0,IPC_RMID)==-1) perror("semctl");
		shmctl(memoria, IPC_RMID, NULL);
		printf("Se han muerto mis hijos, voy a morirme de la pena.\n");
		return 0;
	}
}

}