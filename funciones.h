#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define SIZEDEFLOAT sizeof(float)
#define SIZEDEINT sizeof(int)


// Struct que almacena los datos de una visibilidad junto con el total de visibilidades leídas
struct visibilidad {
	float pos_ejeU, pos_ejeV, parte_real, parte_imaginaria, ruido;
	int n; // Total de visibilidades leídas
};

// Entradas: Puntero a un archivo de texto
// Salidas: Cantidad de lineas del archivo
// Descripción: Cuenta la cantidad de lineas que tiene un archivo de texto
int contarLineas(FILE *fp);

// Entradas: Puntero a un archivo de texto
// Salidas: Puntero a un arreglo de structs de visibilidades
// Descripción: Lee un archivo de texto y guarda las visibilidades en un arreglo de structs
struct visibilidad *leerArchivo(FILE *fp);

// Entradas: Posición en el eje U y Posición en el eje V de una visibilidad
// Salidas: Distancia entre la posición de la visibilidad y el centro
// Descripción: Calcula la distancia entre la posición de la visibilidad y el centro
float calcularDistancia(float pos_ejeU, float pos_ejeV);

// Entradas: Puntero a un string que representa el nombre del archivo de entrada, 
//			 Puntero a un string que representa el nombre del archivo de salida,
//			 Puntero a un int que representa la cantidad de discos,
//			 Puntero a un float que representa el ancho de cada disco,
//			 Puntero a un int que representa el flag de impresión,
//			 Puntero a un int que representa el número de argumentos,
//			 Puntero a un arreglo de strings que representan los argumentos
// Salidas: Ninguna
// Descripción: Lee los argumentos de la línea de comandos y los guarda en variables
void obtenerParametros(char **nombre_archivo, char **nombre_archivo_salida, int *cantidad_discos, 
	float *ancho_disco, int *print_flag, int *argc, char **argv);