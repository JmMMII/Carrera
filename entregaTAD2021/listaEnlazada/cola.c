#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c)
{
    c->fondo=NULL;
    c->frente=NULL;
    return 0;
}

int colaVacia(Cola *c)
{
     	if(c->frente==NULL)
 	return 1;
 	else
 	return 0;   
}

int colaInserta(Cola *c,tipoElemento elemento)
{
    tipoCelda *temp;
    
    if(NULL == ( temp=malloc(sizeof(tipoCelda *))))
    return -1;

    temp->elemento=elemento;
    temp->sig=NULL;
    
    if(colaVacia(c)){
    c->fondo=temp;
    c->frente=temp;
    }
    else{
    c->fondo->sig=temp;
    c->fondo=temp;
    }
    return 0;
    
}

tipoElemento colaSuprime(Cola *c)
{
     	tipoCelda *temp;
 	tipoElemento valor;

	if(NULL == ( temp=malloc(sizeof(tipoCelda *))))
	return -1;

 	
 	if(colaVacia(c))
 	return -2;
 	
 	temp=c->frente;
 	valor=temp->elemento;
 	c->frente=temp->sig;
	free(temp);
 	return valor;
 	
}
