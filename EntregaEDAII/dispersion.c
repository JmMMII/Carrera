#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lee el contenido del fichero hash organizado mediante el método de DISPERSIÓN según los criterios
// especificados en la práctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta función permite visualizar el método de DISPERSIÓN

int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  regConfig regC; 
  int j,nCubo=0,densidadOcupacion;

   f = fopen(fichHash,"rb");
   fread(&regC,sizeof(regConfig),1,f);
   fread(&cubo,sizeof(cubo),1,f); 
   while (!feof(f)){
	for (j=0;j<C;j++) {
        	if (j==0) printf("Cubo %2d (%2d reg. ASIGNADOS)",nCubo,cubo.numRegAsignados);
        	else 	if ((j==1) && cubo.desbordado) printf("DESBORDADO\t\t");
        		else printf("\t\t\t");
		if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",cubo.reg[j].dni, cubo.reg[j].nombre,cubo.reg[j].ape1,cubo.reg[j].ape2,
			    		cubo.reg[j].provincia);
	    	else printf ("\n");
        	}
		nCubo++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   printf("ORGANIZACIÓN MÉTODO DISPERSIÓN:\n\t %d CUBOS y %d CUBOS DESBORDE con capacidad %d\n",
   		regC.nCubos,regC.nCubosDes, C);   
   printf("\t Contiene %d registros de los cuales se han desbordado %d:\n",regC.numReg,regC.numRegDes);
   densidadOcupacion = 100*regC.numReg/((regC.nCubos+regC.nCubosDes)*C);
   printf("Densidad ACTUAL de ocupación: %d \n\t(MÍNIMA permitida %d  MÁXIMA permitida %d)\n",
   				densidadOcupacion,regC.densidadMin,regC.densidadMax);
   if (densidadOcupacion>regC.densidadMax) {
   	printf("No se respeta la densidad máxima de ocupacion\n");
   	return -3;
   }	
   if (densidadOcupacion<regC.densidadMin) {
   	printf("No se respeta la densidad mínima de ocupacion\n");
   	return -4;
   }	
   if ((densidadOcupacion > regC.densidadMin) && (densidadOcupacion < regC.densidadMax))
      	return 0;
   
   return -1;	
}

void creaHvacio(char *fichHash,regConfig *reg){
  FILE *fHash;
  tipoCubo cubo;
  int j;
  int numCubos =reg->nCubos+reg->nCubosDes;
  reg->nCuboDesAct=reg->nCubos;
  reg->numReg=0;
  reg->numRegDes=0;

  memset(&cubo,0,sizeof(cubo));

  fHash = fopen(fichHash,"wb");
  if(fHash==NULL){perror("fopen"); return;}
  fwrite(reg,sizeof(regConfig),1,fHash);
  for (j=0;j<numCubos;j++) fwrite(&cubo,sizeof(cubo),1,fHash);
  fclose(fHash);
}

int  creaHash(char *fichEntrada,char *fichHash, regConfig *regC){
  FILE *fentrada;
  FILE *fsalida;
  tipoAlumno alumno;
  tipoCubo cubo;
  int clave;

  creaHvacio(fichHash,regC);

  fentrada=fopen(fichEntrada,"rb");
  if(fentrada==NULL){ perror("El fichero de entrada no existe\n"); return -1;}

  fsalida=fopen(fichHash,"rb+");
  if(fentrada==NULL){ perror("Error:fopen salida\n"); return -2;}

  fread(&alumno, sizeof(tipoAlumno),1,fentrada);

  while(!feof(fentrada)){
    regC->numReg++;
    clave=atoi(alumno.dni)%regC->nCubos;
    fseek(fsalida,sizeof(regConfig)+clave*sizeof(tipoCubo),SEEK_SET);
    fread(&cubo, sizeof(tipoCubo),1,fsalida);

    if(cubo.desbordado){ //Desbordamiento!!!!!!
      desborde(fsalida,&alumno,regC);
    }else{
      cubo.reg[cubo.numRegAsignados]=alumno;
      cubo.numRegAsignados++;
      if(cubo.numRegAsignados==C) cubo.desbordado=1;
      fseek(fsalida, -1*sizeof(tipoCubo),SEEK_CUR);
      fwrite(&cubo, 1,sizeof(tipoCubo),fsalida);
    }

  fread(&alumno,sizeof(tipoAlumno),1,fentrada);
  }

  fseek(fsalida,0,SEEK_SET);
  fwrite(regC,1,sizeof(regConfig),fsalida);

  fclose(fentrada);
  fclose(fsalida);

  int densidad;
  densidad = 100*regC->numReg/((regC->nCubos+regC->nCubosDes)*C);

  if (densidad>regC->densidadMax) {
    printf("No se respeta la densidad máxima de ocupacion\n");
    return -3;
   }  
   
  if (densidad<regC->densidadMin) {
    printf("No se respeta la densidad mínima de ocupacion\n");
    return -4;
   }
  
  if ((densidad > regC->densidadMin) && (densidad < regC->densidadMax))
        return 0;

  return -5;
}


void desborde(FILE *fHash,tipoAlumno *reg, regConfig *regC){

  tipoCubo cubo;
      regC->numRegDes++;
      fseek(fHash, sizeof(regConfig)+regC->nCuboDesAct*sizeof(tipoCubo),SEEK_SET);
      fread(&cubo, sizeof(tipoCubo),1,fHash);

      cubo.reg[cubo.numRegAsignados]=*reg;
      cubo.numRegAsignados++;
      if(cubo.numRegAsignados==C) cubo.desbordado=1;
      fseek(fHash, -1*sizeof(tipoCubo),SEEK_CUR);
      fwrite(&cubo, 1,sizeof(tipoCubo),fHash);
      if((cubo.numRegAsignados%C)==0){
        regC->nCuboDesAct++;
        if(regC->nCuboDesAct>=(regC->nCubos+regC->nCubosDes)){
        memset(&cubo,0,sizeof(tipoCubo));
        fwrite(&cubo,1,sizeof(tipoCubo),fHash);
        regC->nCubosDes++;
        fseek(fHash, -1*sizeof(tipoCubo), SEEK_CUR); 
        }
      }

}

tipoAlumno *busquedaHash(FILE *f, char *dni, int *nCubo, int *nCuboDes, int *posReg, int *error){
  tipoCubo cubo;
  tipoAlumno *alumno=malloc(sizeof(tipoAlumno));
  regConfig conf;
  int i;

  *error=-1;

  //Inicializar las variables
  fseek(f,0, SEEK_SET);
  if(fread(&conf,sizeof(regConfig),1,f)==-1){ 
    perror("FILE abierto sin opcion de lectura"); 
    *error=-2; 
    return NULL;
  }


  *nCubo=atoi(dni)%conf.nCubos; //Si falla atoi *error=-4;

  fseek(f,sizeof(regConfig)+(*nCubo)*sizeof(tipoCubo),SEEK_SET);
  fread(&cubo,sizeof(tipoCubo),1,f);

  for(i=0;i<cubo.numRegAsignados;i++){
    if(!strcmp(dni,cubo.reg[i].dni)){
      /*
      strcpy(alumno->dni,cubo.reg[i].dni);
      strcpy(alumno->nombre,cubo.reg[i].nombre);
      strcpy(alumno->ape1,cubo.reg[i].ape1);
      strcpy(alumno->ape2,cubo.reg[i].ape2);
      strcpy(alumno->provincia,cubo.reg[i].provincia);
      */
      *alumno=cubo.reg[i];
      *nCuboDes=-1;
      *posReg=i+1;
      *error=0;
      return alumno;
    }
  }

  fseek(f, sizeof(regConfig)+conf.nCubos*sizeof(tipoCubo),SEEK_SET);
  fread(&cubo,sizeof(tipoCubo),1,f);
  *nCuboDes=conf.nCubos;


  while(!feof(f)){
    
    for(i=0;i<cubo.numRegAsignados;i++)
      if(!strcmp(dni,cubo.reg[i].dni)){
        *alumno=cubo.reg[i];
        *posReg=i+1;
        *error=0;
        return alumno;
      }

    fread(&cubo,sizeof(tipoCubo),1,f);
    (*nCuboDes)++;
  }

  return NULL;

}

int modificarReg(char *fichero, char *dni, char *provincia){
  FILE *f=fopen(fichero,"rb+");
  if(f==NULL){perror("fopen"); return -2;}
  tipoCubo cubo;
  tipoAlumno *alumno;
  int nCubos,nCubosDes,posReg,error;

  alumno=busquedaHash(f,dni,&nCubos,&nCubosDes,&posReg,&error);
  
      printf("#######################################################################\n");
      printf("Alumno %s dni %s",alumno->nombre,alumno->dni);
      printf("#######################################################################\n");

  if(error==-1){
    perror("busquedaHash: No encuentra usuario");
    return -1;
  }

  if(error==-2){
    perror("busquedaHash: Problema con el fichero de datos");
    return -2;
  }

  if(error==-4){
    perror("busquedaHash");
    return -4;
  }

  if(nCubosDes==-1){
    fseek(f,sizeof(regConfig)+nCubos*sizeof(tipoCubo),SEEK_SET);
    fread(&cubo,sizeof(tipoCubo),1,f);
    //strcpy(cubo.reg[posReg].provincia,provincia);
    strcpy(cubo.reg[posReg].provincia,"Zamora");
        

    fseek(f, -1*sizeof(tipoCubo),SEEK_CUR);
    fwrite(&cubo,1,sizeof(tipoCubo),f);
    fclose(f);
    return nCubosDes;
  }
  else{
    fseek(f,sizeof(regConfig)+nCubosDes*sizeof(tipoCubo),SEEK_SET);
    fread(&cubo,sizeof(tipoCubo),1,f);
    strcpy(cubo.reg[posReg].provincia,provincia);
    fseek(f, -1*sizeof(tipoCubo),SEEK_CUR);
    fwrite(&cubo,1,sizeof(tipoCubo),f);
    fclose(f);
    return nCubosDes;
  }

}

//Que pasa si regC->nCubosDes=0;


int exportarResultado(char *p){
  FILE *f;
    if((f = fopen(p, "w")) == NULL) {perror("fopen"); return -1;}  //Abrimos fichero
    if(freopen(p, "w", stdout) == NULL) {perror("freopen"); return -1;}  //Volcamos salida estándar
    leeHash("alumnos.hash");
    if(freopen("/dev/tty", "w", stdout) == NULL) {perror("freopen"); return -1;}  //Restauramos salida estándar
    printf("Se ha exportado correctamente el resultado\n");
    if(fclose(f) == -1) {perror("fclose"); return -1;}  //Cerramos fichero
}
