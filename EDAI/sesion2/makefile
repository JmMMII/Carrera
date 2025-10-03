# Proyecto Práctica 2 - Sesión 3

# Para algoritmo Burbuja
medirTyContarV: medirTyContarV.c ordenacion.o
	gcc -g medirTyContarV.c ordenacion.o -o medirTyContarV

ordenacion.o: ordenacion.c ordenacion.h
	gcc -c -g ordenacion.c

# Para Ejercicio 2
medirTyContar: medirTyContar.c algoritmos.o 
	gcc -g medirTyContar.c algoritmos.o -o medirTyContar


algoritmos.o: algoritmos.c algoritmos.h
	gcc -c -g algoritmos.c


clean:
	rm *.o


