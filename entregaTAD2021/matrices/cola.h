#ifndef __COLA_H
#define __COLA_H
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
	int tamagno;
    int frente, fondo;
	tipoElemento elementos[MAX];
	} Cola;



int colaCreaVacia(Cola *c);

// En vacía no sería necesario el paso por referencia
// pero por una cuestión de eficiencia
int colaVacia(Cola *c);

int colaInserta(Cola *c, tipoElemento elemento);

tipoElemento colaSuprime(Cola *c);

#endif
