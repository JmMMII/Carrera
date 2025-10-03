# Proyecto Práctica 2 - Sesión 3 (iterativos) y Sesión 4 (recursivos y recursivos frente a iterativos)

# Análisis experimental de algoritmos que necesitan un vector (burbuja, ejercicio 7 y ejercicio 8)
medirTyContarV: medirTyContarV.c ordenacion.o algoritmos.o
	gcc -g medirTyContarV.c ordenacion.o algoritmos.o -o medirTyContarV

# Análisis experimental de algoritmos que NO necesitan un vector (ejercicio 2, 3, 4 y 6 )
# y el ejercicio 5 pero ... necesita lista.o!!!!

medirTyContar: medirTyContar.c algoritmos.o 
	gcc -g medirTyContar.c algoritmos.o -o medirTyContar


# Reglas para conseguir el codigo objeto de las funciones que se necesitan o se quieren analizar

ordenacion.o: ordenacion.c ordenacion.h
	gcc -c -g ordenacion.c

algoritmos.o: algoritmos.c algoritmos.h
	gcc -c -g algoritmos.c


# Para Ejercicio 5 ¡ se necesita una lista enlazada !
lista.o: lista.c lista.h
	gcc -c -g lista.c

# Ejercicio 5 (solo prueba, no analiza!!)

pruebaEj5: pruebaEj5.c lista.o 
	gcc -g pruebaEj5.c lista.o -o pruebaEj5

clean:
	rm *.o


