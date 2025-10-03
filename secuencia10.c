#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>



int main(){
int i,num=100;
int semaforo;
key_t clave=ftok("Hola qur tal",'H');

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

	if((semaforo=semget(clave,2,IPC_CREAT | 0600))==-1){
	perror("Error en la creacion del semáforo\n");
	return -1;
	}

	if(semctl(semaforo,0,SETVAL,1)==-1) {perror("semctl"); return -1;}
	if(semctl(semaforo,1,SETVAL,0)==-1) {perror("semctl"); return -1;}

	switch(fork()){
	case -1:
	perror("fork()");
	return -1;
	case 0:
	for(i=0;i<num;i++){
	
	  if(semop(semaforo,&menos1,1)==-1){perror("semop"); return -1;}
	  printf("1");
	  fflush(stdout);
	  if(semop(semaforo,&mas2,1)==-1){perror("semop"); return -1;}
	
	}
	return 0;
	default:		
	break;
	}
	
	switch(fork()){
	case -1:
	perror("fork()");
	return -1;
	case 0:
	for(i=0;i<num;i++){
	
	  if(semop(semaforo,&menos2,1)==-1){perror("semop"); return -1;}
          printf("0");
          fflush(stdout);
	  if(semop(semaforo,&mas1,1)==-1){perror("semop"); return -1;}
	
	}
	return 0;
	default:
	break;
	}	

	wait(NULL);
	wait(NULL);
	printf("\n");
	
	if(semctl(semaforo,0,IPC_RMID)==-1){perror("semctl"); return -1;}

return 0;
}
