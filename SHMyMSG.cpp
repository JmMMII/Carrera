#include <iostream>
#include "windows.h"

int TAMANIO = 3 * sizeof(int) + sizeof(char) + sizeof(char) * (4 + 1); //String de 4 carácteres
DWORD WINAPI funcionHijo(LPVOID A);
HANDLE semaforo;

int main()
{
	printf("Soy el Padre\n");
	fflush(stdout);

	//Solicitar SharedMemory al S.O
	HANDLE memoria = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAMANIO, "memoria compartida");

	if (memoria == INVALID_HANDLE_VALUE) {
		//Imprimir error
		return 1;
	}

	//Obtener el puntero a la memoria
	LPINT ref =(LPINT) MapViewOfFile(memoria, FILE_MAP_ALL_ACCESS, 0, 0, TAMANIO);

	//Guardar o leer lo que queramos
	/*
	int valor_a_guardar = 112;
	CopyMemory(ref, &valor_a_guardar, sizeof(valor_a_guardar));
	ref = ref + 4;

	valor_a_guardar = 55;
	CopyMemory(ref, &valor_a_guardar, sizeof(valor_a_guardar));
	ref = ref + 4;
	
	valor_a_guardar = 698;
	CopyMemory(ref, &valor_a_guardar, sizeof(valor_a_guardar));
	ref = ref + 4;

	char letra = 'a';
	CopyMemory(ref, &letra, sizeof(letra));
	ref = ref + 1;

	char frase[5] = "casa";
	CopyMemory(ref, &frase, sizeof(frase));
	ref = ref + 5;
	*/

	ref[0] = 112;
	ref[1] = 114;
	ref[2] = 115;
	ref[3] = 'a';
	
	//Ya no voy a usar la MemoriaCompartida
	if (!UnmapViewOfFile(ref)) {
		//Imprimir error
		return 1;
	}

	DWORD pidHijo;
	semaforo = CreateSemaphore(NULL, 0, 1, NULL);

	HANDLE hijo = CreateThread(NULL, NULL, funcionHijo, NULL, 0, &pidHijo);

	if (hijo == INVALID_HANDLE_VALUE) {
		//Imprimir error
		return 1;
	}

	char tmp[100] = "este es el mensaje";
	WaitForSingleObject(semaforo, INFINITE);

	PostThreadMessage(pidHijo, 100, WPARAM(tmp), LPARAM(45));

	WaitForSingleObject(hijo,INFINITE);

	printf("El hijo ha muerto");
	fflush(stdout);

	if (!CloseHandle(memoria)) {
		//Imprimir error
		return 1;
	}
}

DWORD WINAPI funcionHijo(LPVOID A) {

	HANDLE memoria = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "memoria compartida");

	if (memoria == INVALID_HANDLE_VALUE) {
		//Imprimir error
		return 1;
	}

	LPINT ref = (LPINT)MapViewOfFile(memoria, FILE_MAP_ALL_ACCESS, 0, 0, TAMANIO);
	
	/*
	printf("EL Num1 es %d\r\n", *ref);
	fflush(stdout);
	ref = ref + 4;

	printf("EL Num2 es %d\r\n", *ref);
	fflush(stdout);
	ref = ref + 4;

	printf("EL Num3 es %d\r\n", *ref);
	fflush(stdout);
	ref = ref + 4;

	printf("El caracter es %c\r\n", *ref);
	fflush(stdout);
	ref = ref + 1;

	printf("La frase es %s\r\n", ref); //Para las cadenas el * sobra
	fflush(stdout);
	*/

	printf("EL Num1 es %d\r\n", ref[0]);
	fflush(stdout);

	printf("EL Num2 es %d\r\n", ref[1]);
	fflush(stdout);

	printf("EL Num3 es %d\r\n", ref[2]);
	fflush(stdout);

	printf("El caracter es %c\r\n", ref[3]);
	fflush(stdout);

	//No sé mezclarlo con una frase hay que investigar más

	MSG msg;

	PeekMessage(&msg, NULL, 100, 100, PM_NOREMOVE);
	ReleaseSemaphore(semaforo, 1, NULL);

	if (PeekMessage(&msg, NULL, 500, 500, PM_NOREMOVE) == 0) { //No bloqueante
		//No hay mensaje
		printf("No me he quedado bloqueado\r\n");
		fflush(stdout);
	}

	//Recupero mensaje
	GetMessage(&msg, NULL, 100, 100);
	printf("El valor de WPARAM es %s\r\n", msg.wParam);
	printf("El valor de LPARAM es %d\r\n", msg.lParam);
	fflush(stdout);

	if (!UnmapViewOfFile(ref)) {
		//Imprimir error
		return 1;
	}

	return 0;
}