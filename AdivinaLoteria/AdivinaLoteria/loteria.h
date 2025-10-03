// El siguiente bloque ifdef muestra la forma estándar de crear macros que hacen la exportación
// de un DLL más sencillo. Todos los archivos de este archivo DLL se compilan con LOTERIA_EXPORTS
// símbolo definido en la línea de comandos. Este símbolo no debe definirse en ningún proyecto
// que use este archivo DLL. De este modo, otros proyectos cuyos archivos de código fuente incluyan el archivo verán
// interpretan que las funciones LOTERIA_API se importan de un archivo DLL, mientras que este archivo DLL interpreta los símbolos
// definidos en esta macro como si fueran exportados.
#ifdef LOTERIA_EXPORTS
#define LOTERIA_API __declspec(dllexport)
#else
#define LOTERIA_API __declspec(dllimport)
#endif

extern "C" LOTERIA_API VOID MostrarNumeroCalculado(VOID);
extern "C" LOTERIA_API VOID CalcularNumero(VOID);
extern "C" LOTERIA_API INT RetornarNumero(VOID);
extern "C" LOTERIA_API VOID ImprimirNumero(INT);