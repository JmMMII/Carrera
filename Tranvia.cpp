// EstacionDeAutobuses.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <shlobj.h>
#include <cerrno>
#include "lomo2.h"

#define MAX_TRENES 100
#define ANCHO 75
#define ALTO 17
#define TAM (ANCHO * ALTO)

int (*LOMO_generar_mapa)(char const*, char const*);
int (*LOMO_inicio)(int, int, char const*, char const*);
int (*LOMO_peticiOnAvance)(int, int*, int*);
int (*LOMO_avance)(int, int*, int*);
const char* (*LOMO_getColor)(int);
void (*LOMO_espera)(int, int);
void (*pon_error)(char const*);

HANDLE semaforo;
int flag = 1;

DWORD WINAPI funcionHijo(LPVOID a);

BOOL WINAPI fin(DWORD fdwCtrlType)
{
    if (fdwCtrlType == CTRL_C_EVENT) {

        //Carga de la libreria
        HINSTANCE libreria = LoadLibrary("lomo2.dll");
        if (libreria == NULL) {
            printf("No se ha cargado la libreria\r\n");
            return 1;
        }

        //Bindeos
        FARPROC LOMO_fin = GetProcAddress(libreria, "LOMO_fin");
        if (LOMO_fin == NULL) {
            printf("Problema al asociar el metodo LOMO_fin");
            return 1;
        }

        LOMO_fin();

        //Abrimos la memoria
        HANDLE memoria = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MemoriaMapa");
        if (memoria == INVALID_HANDLE_VALUE) {
            printf("Error al abrir el mapa de memoria: %d\n", GetLastError());
            //fin();
            return 1;
        }

        //Obtenemos la referencia a memoria
        int(*mapa)[ANCHO] = (int(*)[ANCHO])MapViewOfFile(memoria, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * TAM);
        if (mapa == NULL) {
            printf("Error al crear el mapa de memoria: %d\n", GetLastError());
            //fin();
            return 1;
        }
        printf("Ctrl-C event\n\n");

        /*for (int i = 0; i < ALTO; i++) {
            for (int j = 0; j < ANCHO; j++) {
                printf("%d ", mapa[i][j]);
            }
            printf("\r\n");
        }*/

        Sleep(1000);
        return 0;
    }
}
BOOL WINAPI finHijo(DWORD fdwCtrlType)
{

    if (fdwCtrlType == CTRL_C_EVENT) {
        return 0;
    }
}


int main(int argc, char* argv[])
{
    //Control de ctrl+c
    if (SetConsoleCtrlHandler(fin, TRUE) == 0) {
        printf("\nERROR: Could not set control handler");
        return 1;
    }

    //Carga de la libreria
    HINSTANCE libreria = LoadLibrary("lomo2.dll");
    if (libreria == NULL) {
        printf("No se ha cargado la libreria\r\n");
        return 1;
    }

    //Bindeos
    LOMO_generar_mapa = (int (*)(char const*, char const*))GetProcAddress(libreria, "LOMO_generar_mapa");
    if (LOMO_generar_mapa == NULL) {
        printf("Problema al asociar el metodo LOMO_generar_mapa");
        return 1;
    }

    LOMO_inicio = (int (*)(int, int, char const*, char const*))GetProcAddress(libreria, "LOMO_inicio");
    if (LOMO_generar_mapa == NULL) {
        printf("Problema al asociar el metodo LOMO_inicio");
        return 1;
    }

    int retardo, tamMaximo, nTrenes;
    if ((argc == 2) && (strcmp(argv[1], "--mapa") == 0)) {

        char desktop[MAX_PATH];

        if (SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktop) != S_OK) { perror("Error al obtener la ruta del escritorio.\n"); return 1; }
        strcat_s(desktop, "\\mapa.html");

        FILE* f = nullptr;

        if (freopen_s(&f, desktop, "wt", stdout) != 0) { perror("Error al abrir el archivo.\n"); return 1; }

        LOMO_generar_mapa("i8735101", "i1045393");

        if (fclose(f) != 0) { perror("Error al cerrar el archivo\r\n"); return 1; }

        return 0;

    }
    else if ((argc == 4) && ((retardo = atoi(argv[1])) >= 0) && ((tamMaximo = atoi(argv[2])) >= 3) && (atoi(argv[2]) <= 19) && ((nTrenes = atoi(argv[3])) > 0) && (atoi(argv[3]) <= 100)) {
        
        //Reserva del mapa
        HANDLE shmapa = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int) * TAM, "MemoriaMapa"); //Handle del mapa
        if (shmapa == INVALID_HANDLE_VALUE) {
            printf("Error al crear el archivo mapeado: %d\n", GetLastError());
            return 1;
        }

        //Referencia al mapa
        int(*mapa)[ANCHO] = (int(*)[ANCHO])MapViewOfFile(shmapa, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * TAM);
        if (mapa == NULL) {
            printf("Error al crear el mapa de memoria: %d\n", GetLastError());
            CloseHandle(shmapa);
            return 1;
        }

        //Inicializacion del mapa
        for (int i = 0; i < ALTO; i++) {
            for (int j = 0; j < ANCHO; j++) {
                mapa[i][j] = -1;
            }
        }

        //Reserva del vector
        HANDLE shvector = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int) * (MAX_TRENES+1) * 2, "VectorTren");
        if (shvector == INVALID_HANDLE_VALUE) {
            printf("Error al crear el archivo mapeado: %d\n", GetLastError());
            return 1;
        }

        //Referencia al vector
        int (*vector)[2] = (int(*)[2])MapViewOfFile(shvector, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * (MAX_TRENES + 1) * 2);
        if (vector == NULL) {
            printf("Error al crear el mapa de memoria: %d\n", GetLastError());
            CloseHandle(shvector);
            return 1;
        }

        //Inicializacion del mapa
        for (int i = 0;i < (MAX_TRENES + 1);i++) {
            vector[i][0] = -1;
            vector[i][1] = -1;
        }

        //Inicializacion semaforos
        semaforo = CreateSemaphore(NULL, 1, 1, "semaforo");
        if (semaforo == NULL) {
            printf("Error al crear el semáforo\r\n");
            return 1;
        }
        HANDLE hijos[MAX_TRENES];

        if (LOMO_inicio(retardo, tamMaximo, "i1045393", "i8735101") == -1) {
            perror("LOMO_INICIO");
            return -1;
        }
        

        for (int i = 0; i < nTrenes; i++) {
            hijos[i] = CreateThread(NULL, 0, funcionHijo, LPVOID(nTrenes), 0, NULL);
        }

        Sleep(10000);
        flag = 0;

        for (int i = 0; i < nTrenes; i++) {
            WaitForSingleObject(hijos[i], INFINITE);
        }
        
        for (int i = 0; i < ALTO; i++) {
            for (int j = 0; j < ANCHO; j++) {
                printf("%d", mapa[i][j]);
                fflush(stdout);
            }
            printf("\n");
            fflush(stdout);
        }

        printf("\n");
        fflush(stdout);
        printf("\n");
        fflush(stdout);

        for (int i = 0;i < nTrenes;i++)
            printf("%d: %d %d\n",i, vector[i][0], vector[i][1]);



        return 0;
    }
    else {
        printf("Error, argumentos incorrectos:\r\n");
        printf("Opcion 1 lomo --mapa.\r\n");
        printf("Opcion 2 lomo retardo nTrenes. (retardo >= 0) (3 <= tamMAximo <= 19) (0 < nTrenes <= 100)\r\n");

        return 1;
    }

}

DWORD WINAPI funcionHijo(LPVOID nTrenes) {

    //Control de ctrl+c
    if (SetConsoleCtrlHandler(finHijo, TRUE) == 0) {
        printf("\nERROR: Could not set control handler");
        return 1;
    }

    //Paso 1 Cargar la libreria en codigo
    HINSTANCE libreria = LoadLibrary("lomo2.dll");
    if (libreria == NULL) {
        printf("No se ha cargado la libreria\r\n");
        return 1;
    }

    //Paso 2 Hacer los Bindeos    
    LOMO_inicio = (int (*)(int, int, char const*, char const*))GetProcAddress(libreria, "LOMO_inicio");
    if (LOMO_generar_mapa == NULL) {
        printf("Problema al asociar el metodo LOMO_inicio");
        return 1;
    }
    FARPROC LOMO_autobusNuevo = GetProcAddress(libreria, "LOMO_trenNuevo");
    if (LOMO_autobusNuevo == NULL) {
        printf("Problema al asociar el metodo LOMO_trenNuevo");
        return 1;
    }
    LOMO_peticiOnAvance = (int (*)(int, int*, int*))GetProcAddress(libreria, "LOMO_peticiOnAvance");
    if (LOMO_peticiOnAvance == NULL) {
        printf("Problema al asociar el metodo LOMO_peticiOnAvance");
        return 1;
    }
    LOMO_avance = (int (*)(int, int*, int*))GetProcAddress(libreria, "LOMO_avance");
    if (LOMO_avance == NULL) {
        printf("Problema al asociar el metodo LOMO_avance");
        return 1;
    }
    LOMO_getColor = (const char* (*)(int))GetProcAddress(libreria, "LOMO_getColor");
    if (LOMO_getColor == NULL) {
        printf("Problema al asociar el metodo LOMO_getColor");
        return 1;
    }
    LOMO_espera = (void (*)(int, int))GetProcAddress(libreria, "LOMO_espera");
    if (LOMO_espera == NULL) {
        printf("Problema al asociar el metodo LOMO_espera");
        return 1;
    }
    FARPROC refrescar = GetProcAddress(libreria, "refrescar");
    if (refrescar == NULL) {
        printf("Problema al asociar el metodo refrescar");
        return 1;
    }
    pon_error = (void (*)(char const*))GetProcAddress(libreria, "pon_error");
    if (pon_error == NULL) {
        printf("Problema al asociar el metodo pon_error");
        return 1;
    }

    //Abrimos la memoria
    HANDLE shmapa = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MemoriaMapa");
    if (shmapa == INVALID_HANDLE_VALUE) {
        printf("Error al abrir el mapa de memoria: %d\n", GetLastError());
        //fin();
        return 1;
    }

    //Referencia a memoria
    int(*mapa)[ANCHO] = (int(*)[ANCHO])MapViewOfFile(shmapa, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * TAM);
    if (mapa == NULL) {
        printf("Error al crear el mapa de memoria: %d\n", GetLastError());
        //fin();
        return 1;
    }

    HANDLE  shvector = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "VectorTren");
    if (shvector == INVALID_HANDLE_VALUE) {
        printf("Error al abrir el mapa de memoria: %d\n", GetLastError());
        //fin();
        return 1;
    }

    int (*vector)[2] = (int(*)[2])MapViewOfFile(shvector, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * (MAX_TRENES + 1) * 2);

    semaforo = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, "semaforo");
    if (semaforo == NULL) {
        pon_error("OpenSemaphore");
        // fin();
    }

    MSG msg;
    int retorno, xAnt, yAnt;
    int x = 0;
    int y = 0;
    int x1, y1;
    int autobus = LOMO_autobusNuevo();
    vector[autobus][1] = GetCurrentThreadId();
    
    while (flag) {
        xAnt = x; yAnt = y;
        LOMO_peticiOnAvance(autobus, &x, &y);
        WaitForSingleObject(semaforo, INFINITE);
        if (mapa[y][x] == -1) {
            mapa[y][x] = autobus;
            vector[autobus][0] = -1; 
            LOMO_avance(autobus, &x1, &y1);
            
            if (x1 != -1) { 
                mapa[y1][x1] = -1;
            }
            LOMO_espera(y, yAnt);

            for (int i = 0;i < 9;i++) {
                if (vector[i][0] == autobus)
                    PostThreadMessage(vector[i][1], autobus+1, WPARAM(0), LPARAM(0));
            }

            ReleaseSemaphore(semaforo, 1, NULL);
        }
        else {
            vector[autobus][0] = mapa[y][x];
            ReleaseSemaphore(semaforo, 1, NULL);
            GetMessage(&msg, NULL, vector[autobus][0]+1, vector[autobus][0]+1);
        }
    }
}

//Conjuntos
/*
* La primera casilla se ignora
* Se considera que un tren está esperando cuando vector[autobus+1][0]!=0
* la primera columna indica el tren al que está esperando
* la segunda columna indica el pid del hilo correspondiente al autobus cuyo id sea el indice
*/