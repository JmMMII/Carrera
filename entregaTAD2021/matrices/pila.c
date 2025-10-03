#include "pila.h"



int pilaCreaVacia(Pila *p)
{
	p->tope=0;
	return 0;
}


// En vacía no sería necesario el paso por referencia
// pero por una cuestión de eficiencia
int pilaVacia(Pila *p)
{
	if(p->tope==0)
	return 1;
	else
	return 0;
}

int pilaInserta(Pila *p,tipoElemento elemento)
{
	if(p->tope==MAX-1)
	return -1;
	else{
	p->tope=p->tope+1;
	p->elementos[p->tope]=elemento;
	return 0;
	}
}

tipoElemento pilaSuprime(Pila *p)
{
	tipoElemento x;
	if(pilaVacia(p))
	return -1;
	else{
	x=p->elementos[p->tope];
	p->tope=p->tope-1;
	return x;
	}
}


