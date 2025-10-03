/*
 * lista.c
 *
 *  Created on: 20/10/2014
 *      Author: MJ Polo
 */

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

// Crea una lista enlazada de "n" nodos con valores enteros entre 0 y (rango - 1)
nodo * creaLista(int n, int rango)
{ nodo * lista=NULL, *aux;
  int i;
  for (i = 0; i < n ; i++)
  { aux = (nodo *)malloc (sizeof (nodo));
    aux->info = rand () % rango ;
    aux->sig = lista;
    lista = aux;
  }
  return lista;
}

// Muestra el contenido de una lista enlazada de enteros
void verLista(nodo *lista)
{ nodo *aux;
  aux = lista;
    while (aux!=NULL)
    { printf(" %d  ", aux->info);
      aux = aux->sig;
    }
}

// Libera la memoria reservada para los nodos de una lista. Al finalizar la función la lista esta vacia (NULL)

void liberarLista(nodo *lista)
{ nodo *aux, *borrar;
  aux = lista;
    while (aux!=NULL)
    { borrar =aux;
      aux = aux->sig;
      free(borrar);
    }

}

// Enuniciado 5. Muestra el contenido de una lista enlazada de enteros en orden inverso (desde el último al primero) 
void verListaInverso(nodo *lista)
{ 


}

