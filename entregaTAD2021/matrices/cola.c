#include "cola.h"

int colaCreaVacia(Cola *c)
{
	c->tamagno=0;
	c->frente=0;
	c->fondo=MAX-1;
	return 0;
}

// En vacía no sería necesario el paso por referencia
// pero por una cuestión de eficiencia
int colaVacia(Cola *c)
{
	if(c->tamagno==0)
	return 1;
	else
	return 0;
}

int incrementaIndice(int *x)
{
	if(*x==MAX-1)
	*x=0;
	else
	*x=*x+1;
	
	return 0;
}
int colaInserta(Cola *c, tipoElemento elemento)
{
	if(c->tamagno==MAX-1)
	return -1;
	else{
	incrementaIndice(&(c->fondo));
	c->elementos[c->fondo]=elemento;
	c->tamagno=c->tamagno+1;
	return 0;
	}
}

tipoElemento colaSuprime(Cola *c)
{
	tipoElemento valor;
	
	if(colaVacia(c))
	return -1;
	else{
	valor=c->elementos[c->frente];
	incrementaIndice(&(c->frente));
	c->tamagno=c->tamagno-1;
	return valor;
	}
}
