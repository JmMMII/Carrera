#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p)
{
	*p=NULL;
	return 0;
}

int pilaVacia(Pila *p)
{
 	if(*p==NULL)
 	return 1;
 	else
 	return 0;   
}

int pilaInserta(Pila *p,tipoElemento elemento)
{
	Pila temp;
	if(NULL == ( temp=malloc(sizeof(Pila))))
	return -1;
	
	temp->elemento=elemento;
	
	if(pilaVacia(p)){
	temp->sig==NULL;
	*p=temp;
	}
	else{
	temp->sig=*p;
	*p=temp;
	}
	
	return 0;
}

tipoElemento pilaSuprime(Pila *p)
{
 	Pila temp;
 	tipoElemento valor;
 	
	if(NULL == (temp = malloc(sizeof(Pila))))
	return -1;

 	if(pilaVacia(p))
 	return -2;
 	
 	valor=(*p)->elemento;
 	temp=*p;
 	*p=temp->sig;
 	free(temp);
 	return valor;
 	
 		   
}
