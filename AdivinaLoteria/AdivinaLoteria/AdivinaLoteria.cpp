// AdivinaLoteria.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "windows.h"
#include "loteria.h"

//Valor que devuelve (*nombredefuncion) (tipoparamquepasamos)
VOID(*ImprimirNumerito) (int); //nombredefuncion no puede ser igual al nombre de la funcion a la que estamos haciendo un bindeo

int main()
{
    //Cargar libreria en codigo
    HINSTANCE libreria = LoadLibrary("loteria.dll");
    if (libreria == NULL) {
        printf("No se ha cargado la libreria\r\n");
        return 1;
    }

    //Hacer los bindeos
    FARPROC MostrarNumeroCalculado = GetProcAddress(libreria, "MostrarNumeroCalculado");
    if (MostrarNumeroCalculado == NULL) {
        printf("Problema al asociar el metodo MostrarNumeroCalculado");
        return 1;
    }

    FARPROC RetornarNumero = GetProcAddress(libreria, "RetornarNumero");
    if (RetornarNumero == NULL) {
        printf("Problema al asociar el metodo RetornarNumero");
        return 1;
    }

    FARPROC CalcularNumero = GetProcAddress(libreria, "CalcularNumero");
    if (CalcularNumero == NULL) {
        printf("Problema al asociar el metodo CalcularNumero");
        return 1;
    }

    //Bindeo de funcion con param
    //(VALOR QUE DEVUELVE (*) (TIPO DE DATO QUE LE PASAMOS))
    ImprimirNumerito = (VOID(*) (int)) GetProcAddress(libreria, "ImprimirNumero");
    if (ImprimirNumerito == NULL) {
        printf("Problema al asociar el metodo ImprimirNumero");
        return 1;
    }

    MostrarNumeroCalculado();
    CalcularNumero();
    int retorno = RetornarNumero();
    printf("Valor libreria retornado %d\r\n", retorno);
    ImprimirNumerito(98);

    FreeLibrary(libreria);
}

