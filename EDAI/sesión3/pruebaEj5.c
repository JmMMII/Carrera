/*
 * pruebaEj5.c  Prueba de funciones que permiten crear y ver una lista en orden directo (del primer nodo al último)
 *              e inverso (del último al primero)
 *
 *  Created on: 20/10/2014
 *      Author: MJ Polo
 */

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"


int main(int argc, char *argv[])
{ nodo *lista;

 
  lista = creaLista(5,100); 
  verLista(lista);

  // Enunciado 5: Mostrar por pantalla en orden inverso los numeros de una lista enlazada
  printf("\nImplementar función recursiva que muestre los elementos de la lista en orden inverso \n\n");
   verListaInverso(lista);


  printf("\nImplementar función para liberar los nodos de la lista  \n\n");
   liberarLista(lista);


return 0;
}
