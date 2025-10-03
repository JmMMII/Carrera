#ifndef __PILA_H
#define __PILA_H
#include <stdio.h>

#ifndef TIPO_ELEMENTO
typedef int tipoElemento;
#define TIPO_ELEMENTO
#endif

#ifndef MAX
#define MAX 100
#endif


//Se puede utilizar como valor constante en gestión de errores
#ifndef INF
#define INF 999999999
#endif


typedef struct {
    int tope;
    tipoElemento elementos[MAX];
} Pila;
	


int pilaCreaVacia(Pila *p);


// En vacía no sería necesario el paso por referencia
// pero por una cuestión de eficiencia
int pilaVacia(Pila *p);

int pilaInserta(Pila *p,tipoElemento elemento);

tipoElemento pilaSuprime(Pila *p);


#endif
