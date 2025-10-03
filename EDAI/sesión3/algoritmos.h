/*
 * algoritmos.h
 *
 *  Created on: 07/10/2013
 *      Author: MJ Polo
 */

#ifndef ALGORITMOS_H_INCLUDED
#define ALGORITMOS_H_INCLUDED
#define MIN_T 10 * CLOCKS_PER_SEC
#define MIN_REP 5
extern long int contadorInterno, contadorExterno, contadorMedio;

void algA(int n);
void algB(int n);
void algC(int n);
void algD(int n);
void algE(int n);
void algF(int n);
void algG(int n);
void algH(int n);
void algI(int n);
void algJ(int n);

//Enunciado 3
double factorialR(int n);
double factorialI(int n);
// Enunciado 4
int fibonnacciR(int n);
int fibonnacciI(int n);
// Enunciado 5 En lista.c

// Enunciado 6
double potR(int x,int n);
double potI(int x,int n);
// Enunciado 7
int algoritmo7(int *vector,int base,int tope);
//Enunciado 8
int algoritmo8(int *vector,int base,int tope, int numElementos);
void verSubvector(int *vector, int base, int tope);

#endif // ALGORITMOS_H_INCLUDED
