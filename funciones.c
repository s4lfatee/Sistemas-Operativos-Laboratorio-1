#include "funciones.h"

// Entradas: Puntero a un archivo de texto
// Salidas: Cantidad de lineas del archivo
// Descripción: Cuenta la cantidad de lineas que tiene un archivo de texto
int contarLineas(FILE *fp){
    int count = 0;
    char c;
    while ((c = fgetc(fp)) != EOF){
        if (c == '\n'){
            count++;
        }
    }
    return count;
}

// Entradas: Puntero a un archivo de texto
// Salidas: Puntero a un arreglo de structs de visibilidades
// Descripción: Lee un archivo de texto y guarda las visibilidades en un arreglo de structs
struct visibilidad *leerArchivo(FILE *fp){
    int n = contarLineas(fp); // Debemos calcular el numero de lineas para reservar memoria
    rewind(fp); // Debemos volver al inicio del archivo debido a que contarLineas ya recorrió el archivo
	struct visibilidad *visibilidades = malloc(sizeof(struct visibilidad) * n);
	float i, j, k, l, m;
	int x = 0;
	struct visibilidad aux; // Se crea un struct auxiliar para rellenar el arreglo
	aux.n = n; // Se almacena el tamaño del archivo leído para asignar memoria en el programa
	while (fscanf(fp, "%f,%f,%f,%f,%f", &i, &j, &k, &l, &m) != EOF){
		aux.pos_ejeU = i;
		aux.pos_ejeV = j;
		aux.parte_real = k;
		aux.parte_imaginaria = l;
		aux.ruido = m;
		visibilidades[x] = aux;
		x++; // Se avanza a la siguiente posición del arreglo
	}
	fclose(fp);
	return visibilidades;
}

// Entradas: Posición en el eje U y Posición en el eje V de una visibilidad
// Salidas: Distancia entre la posición de la visibilidad y el centro
// Descripción: Calcula la distancia entre la posición de la visibilidad y el centro
float calcularDistancia(float pos_ejeU, float pos_ejeV){
	return sqrt(pow(pos_ejeU, 2) + pow(pos_ejeV, 2));
}

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
	float *ancho_disco, int *print_flag, int *argc, char **argv){
	int opt;
	while((opt = getopt(*argc, argv, "i:o:n:d:b")) != -1){
		switch(opt){
			case 'i':
				*nombre_archivo = optarg;
				break;
			case 'o':
				*nombre_archivo_salida = optarg;
				break;
			case 'n':
				*cantidad_discos = atoi(optarg); // atoi() convierte un string a int
				break;
			case 'd':
				*ancho_disco = atof(optarg); // atof() convierte un string a float
				break;
			case 'b':
			    *print_flag = 1; // Independiente de lo que se ingrese, colocando el parametro -b activará el flag
				break; 
		}
	}
}

