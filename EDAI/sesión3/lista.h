/*
 *  lista.h
 *
 *  Created on: 20/10/2014
 *      Author: MJ Polo
 */
#ifndef __LISTA_H
#define __LISTA_H

typedef struct tagnodo{ 
	int info;
	struct tagnodo *sig;
  } nodo;


nodo * creaLista(int numElementos, int rango);
void verLista(nodo *lista);
void liberarLista(nodo *lista);
// Enunciado 5
void verListaInverso(nodo *lista);

#endif
