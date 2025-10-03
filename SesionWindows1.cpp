// SesionWindows1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "windows.h"
#define PERROR(a) \
    {             \
        LPVOID lpMsgBuf;                                      \
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |        \
                   FORMAT_MESSAGE_FROM_SYSTEM |               \
                   FORMAT_MESSAGE_IGNORE_INSERTS, NULL,       \
                   GetLastError(),                            \
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
                   (LPTSTR) &lpMsgBuf,0,NULL );               \
        fprintf(stderr,"%s:%s\n",a,lpMsgBuf);                 \
        LocalFree( lpMsgBuf );                                \
    }

DWORD WINAPI funcionHijo(LPVOID a);

int main(int argc,char* argv[])
{	
	/*
	printf("Numero de argumendos %d\n",argc);
	fflush(stdout);

	if (argc < 2) {
		printf("Error Argumentos\r\n");
		fflush(stdout);
		return 0;
	}

	printf("Arg1 es %d", atoi(argv[1]));
	fflush(stdout);
	*/

    /*
    PROCESS_INFORMATION informaciOn;
    STARTUPINFO         suinfo;

    /* O bien rellenamos la estructura "a mano" */
    /*
    suinfo.cb = sizeof(suinfo);
    suinfo.lpReserved = NULL;
    suinfo.lpDesktop = NULL;
    suinfo.lpTitle = NULL;
    suinfo.dwFlags = 0;
    suinfo.cbReserved2 = 0;
    suinfo.lpReserved2 = NULL;
    /* O usamos la llamada a la API siguiente... */
    /*
    GetStartupInfo(&suinfo);

    if (!CreateProcess(NULL, LPSTR("Firefox"), NULL, NULL, false,
        CREATE_NEW_PROCESS_GROUP, NULL,
        NULL, &suinfo, &informaciOn))
    {
        //fprintf(stderr, "CreateProcess: error %d.\n", GetLastError());
        PERROR("error --> ");
        return 1;
    }
    */

    printf("Soy el Padre\r\n");
    fflush(stdout);

    //Vamos a crear un hijo
    HANDLE hijos[3];

    hijos[0]= CreateThread(NULL, 0, funcionHijo, LPVOID('+'), 0, NULL);
    hijos[1] = CreateThread(NULL, 0, funcionHijo, LPVOID('-'), 0, NULL);
    hijos[2] = CreateThread(NULL, 0, funcionHijo, LPVOID('*'), 0, NULL);

    WaitForMultipleObjects(3,hijos,TRUE,INFINITE);

    printf("Este texto es del padre\r\n");
    fflush(stdout);
}

DWORD WINAPI funcionHijo(LPVOID a) {
    for (int i = 0; i < 100; i++) {
        printf("%c\r\n", a);
        fflush(stdout);
    }
    return 0;
}