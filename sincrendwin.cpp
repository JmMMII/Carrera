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

DWORD WINAPI funcionHijo1(LPVOID a);
DWORD WINAPI funcionHijo2(LPVOID a);

HANDLE sem1, sem2;

int main(int argc, char* argv[])
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
    HANDLE hijos[2];

    sem1 = CreateSemaphore(NULL, 1, 1, NULL);
    sem2 = CreateSemaphoreA(NULL, 0, 1, NULL);


    hijos[0] = CreateThread(NULL, 0, funcionHijo1, LPVOID('0'), 0, NULL);
    hijos[1] = CreateThread(NULL, 0, funcionHijo2, LPVOID('1'), 0, NULL);
    //PulseEvent(evento1);
    WaitForMultipleObjects(2, hijos, TRUE, INFINITE);

    printf("Este texto es del padre\r\n");
    fflush(stdout);
    
    CloseHandle(hijos[0]);
    CloseHandle(hijos[1]);
    CloseHandle(sem1);
    CloseHandle(sem2);
}

DWORD WINAPI funcionHijo1(LPVOID a) {
    

        for (int i = 0; i < 100; i++) {
            WaitForSingleObject(sem1, INFINITE);
            printf("%c\r\n", a);
            fflush(stdout);
            ReleaseSemaphore(sem2,1,NULL);
        }
        return 0;
}

DWORD WINAPI funcionHijo2(LPVOID a) {

    for (int i = 0; i < 100; i++) {
        WaitForSingleObject(sem2, INFINITE);
        printf("%c\r\n", a);
        fflush(stdout);
        ReleaseSemaphore(sem1, 1, NULL);
    }
    return 0;
}