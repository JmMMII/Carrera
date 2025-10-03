#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(){

	regConfig conf;
	conf.nCubos=10;
	conf.nCubosDes=4;
	conf.densidadMax=50;
	conf.densidadMin=20;
	conf.numReg=0;
	conf.numRegDes=0;
	printf("Retorno de creaHash: %d\n", creaHash("alumnos.dat","alumnos.hash", &conf));
	leeHash("alumnos.hash");

	exportarResultado("resultados10_4.txt");
	tipoAlumno *alumno;
	int nCubos,nCubosDes,posReg,error;
	FILE *f=fopen("alumnos.hash","rb");
	if (f==NULL){ perror("fopen"); return 0;}
	alumno=busquedaHash(f,"8393920",&nCubos,&nCubosDes,&posReg,&error);
	printf("Alumno:%s %s nCubos:%d nCubosDes:%d posReg:%d error:%d\n",alumno->nombre,alumno->ape1,nCubos,nCubosDes,posReg,error);
	free(alumno);
	fclose(f);

	printf("Codigo de error %d\n",modificarReg("alumnos.hash","33333333","Zamora"));
	modificarReg("alumnos.hash","33333333","Zamora");
	leeHash("alumnos.hash");

}

