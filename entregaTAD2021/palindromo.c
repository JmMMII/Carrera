
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef MATRICES
#include "matrices/pila.h"
#include "matrices/cola.h"
#elif LISTA_ENLAZADA
#include "listaEnlazada/pila.h"
#include "listaEnlazada/cola.h"
#endif


#define DIM 82


int   palindromo (const char *);
void  convertir_mayusculas (char *);

int main (void) 
{
	
	char cadena[DIM];
	int  espalindromo;

	printf("Introduzca una cadena (max. %d caracteres): ", DIM-2);
	fgets(cadena, DIM - 2, stdin);
	
	//Eliminamos el carácter retorno de carro leído por fgets
	int l = strlen(cadena);
	cadena[l - 1] = '\0';

	convertir_mayusculas (cadena);
	espalindromo = palindromo (cadena);
    
	printf("La cadena %s \n", cadena);
	if (espalindromo)
		printf("Es un palindromo.\n");
	else   
		printf("No  es un palindromo.\n");
     
	return 0;
} 


void convertir_mayusculas (char *cad) 
{
	int j = 0;

	while (cad[j] != '\0') {
		cad[j] = toupper(cad[j]);
		j++;
	}
}


int palindromo (const char *expresion) 
{
	Pila p;
	Cola c;
	int i=0;

	pilaCreaVacia(&p);
	colaCreaVacia(&c);
	
	while(expresion[i]!='\0'){
	if(expresion[i]!=' '){
	pilaInserta(&p, expresion[i]);
	colaInserta(&c, expresion[i]);
	}
	i++;
	}
	
	while(pilaVacia(&p)==0){
	if(colaSuprime(&c)!=pilaSuprime(&p))
	return 0;
	}
	
	return 1;
	
}



