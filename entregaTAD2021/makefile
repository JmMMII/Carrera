CC = gcc


all: palindromoM palindromoL

# Implementación mediante matrices
# Ejecutar: make palindromoM

palindromoM:palindromoM.o matrices/pila.o matrices/cola.o  
	$(CC) -g palindromoM.o matrices/pila.o matrices/cola.o -o palindromoM
	
palindromoM.o: palindromo.c matrices/pila.h matrices/cola.h
	$(CC) -DMATRICES -c -g palindromo.c -o palindromoM.o
	  
matrices/pila.o: matrices/pila.c matrices/pila.h 
	$(CC) -c -g matrices/pila.c -o matrices/pila.o
	
matrices/cola.o: matrices/cola.c matrices/cola.h 
	$(CC) -c -g matrices/cola.c -o matrices/cola.o


# Implementación mediante listas simplemente enlazadas
# Ejecutar: make palindromoL

palindromoL:palindromoL.o listaEnlazada/pila.o listaEnlazada/cola.o  
	$(CC) -g palindromoL.o listaEnlazada/pila.o listaEnlazada/cola.o -o palindromoL
	
palindromoL.o: palindromo.c listaEnlazada/pila.h listaEnlazada/cola.h
	$(CC) -DLISTA_ENLAZADA -c -g palindromo.c -o palindromoL.o
	  
listaEnlazada/pila.o: listaEnlazada/pila.c listaEnlazada/pila.h 
	$(CC) -c -g listaEnlazada/pila.c -o listaEnlazada/pila.o
	
listaEnlazada/cola.o: listaEnlazada/cola.c listaEnlazada/cola.h 
	$(CC) -c -g listaEnlazada/cola.c -o listaEnlazada/cola.o


clean:
	rm palindromoL palindromoM *.o listaEnlazada/*.o matrices/*.o

