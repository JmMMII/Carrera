/*
 * algoritmos.c
 *
 *  Created on: 07/10/2013
 *      Author: MJ Polo
 */
#include <math.h>
#include "algoritmos.h"
// Orden cuadrático
void algA(int n)
{ int i,j,c;

	c = 1;
	for (i=1;i<=n;i++){
		for (j=1;j<=n;j++) {
			c = c + 1;
		}
  	}
}


void algB(int n){
	int i,j,k,c;
	c=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			for(k=1;k<=2;k++){
			c = c + 1; 
			}
		}
	}
}

void algC(int n){
	int i,j,k,c;
	c=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=(n*n);j++){
			for(k=1;k<=(n*n*n);k++){
			c = c + 1;
			}
		}
	}
}

void algD(int n){
	int i,j,c;
	c=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++){
		c = c + 1;
		}
	}
}

void algE(int n){
	int i,j,k,c;
	c=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			for(k=1;k<=j;k++){
			c = c + 1; 
			}
		}
	}
}

void algF(int n){
	int i,j,k,c;
	c=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++){
			for(k=1;k<=j;k++){
			c = c + 1;
			}
		}
	}
}

void algG(int n){
	int j,x;
	x=0;
	j=n;

	while(j>=1){
	x=x+1;
	j=j/2;
	}
}

void algH(int n){
	int j,x;
	x=0;
	j=n;
	
	while(j>=1){
	x=x+1;
	j=j/3;
	}
}

void algI(int n){
	int i,j,x;
	x=0;
	i=1;

	do{
	j=1;	
	while(j<=i){
	x=x+1;
	j=j*2;
	}
	i=i+1;
	}while(i>n);
}

void algJ(int n){
	int i,j,x;
	x=0;
	i=1;
	
	do{
	j=1;
	while(j<=i){
	x=x+1;
	j=j+2;
	}
	i=i+1;
	}while(i>n);
}

int algK(int n){
	int i,j,x;
	x=0;
	i=1;
	while(i<n){
	for(j=1;j<=i;j++){
		x=x+1;
		}
	i=i*10;
	}

return x;
}
