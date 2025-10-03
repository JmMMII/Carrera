/*
 * medirTyContarBur.c
 *
 *  Created on: 29/09/2014
 *      Author: M.J. Polo
 */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacion.h"
#include <time.h>

long int contadorInterno, contadorExterno, contadorK;

int main(int argc, char *argv[])
{ 
	//clock_t tiempoInicial , tiempoFinal ;
	double tiempoInicial , tiempoFinal, tiempoMinimo=10*CLOCKS_PER_SEC ;
	
        double tiempo;

	int *vector, *vectorOrdenado, rango=100000, n=10000,i,repeticiones=0;
        
 	FILE *f;  
 	
	if (argc != 2) {
            printf("\n Uso: ./medirTyContarV <nombre fichero resultados>\n\n");
            return -1;
        }

        f = fopen(argv[1], "w+");
        fprintf(f,"n;tiempoMedio;Externo;Interno\n");


        for (n=5000;n<=50000;n=5000+n) {
                 repeticiones=contadorInterno=contadorExterno=0;
		vector = crearVector(n,rango);

     		tiempoInicial = tiempoFinal= (double)clock();
		while ((tiempoFinal-tiempoInicial < tiempoMinimo) || (repeticiones < 5))
		{ 	vectorOrdenado = ordenarBurbuja(vector,n);
	        	free(vectorOrdenado);	  
			repeticiones++;
	     		tiempoFinal = (double) clock();
		}

     		

     		tiempo =  (tiempoFinal - tiempoInicial ) / (double)CLOCKS_PER_SEC /repeticiones;
		printf("\n %d \t %e \t %ld \t %ld", n,tiempo,contadorExterno/repeticiones,contadorInterno/repeticiones);
		fprintf(f,"\n %d \t %e \t %ld \t %ld", n,tiempo,contadorExterno/repeticiones,contadorInterno/repeticiones);

      free(vector);
      }
fclose(f);

   
return 0;
}


