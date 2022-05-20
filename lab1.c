#include "funciones.h"

int main(int argc, char *argv[]){
	char *nombre_archivo; // nombre del archivo a leer, que cambiará a través del parametro -i
	char *nombre_archivo_salida; // nombre del archivo a escribir, que cambiará a través del parametro -o
	int cantidad_discos, print_flag; // Variables que cambiarán dependiendo de los parametros -n y -b 
	float ancho_disco; // Variable que almacenará el ancho del disco a través del parametro -d
	float pr, pi, ruido, potencia; // Variables que leerán la parte real, imaginaria y ruido de una visibilidad
	int cantidad, pid_hijo; // Variables que almacenan la cantidad de visibilidades leídas y el pid del procesos hijos


	obtenerParametros(&nombre_archivo, &nombre_archivo_salida, &cantidad_discos, &ancho_disco, &print_flag, &argc, argv);


	int pipes_entrada[cantidad_discos][2]; // Matriz de N pipes de entrada
	int pipes_salida[cantidad_discos][2]; // Matriz de N pipes de salida
	
	// Se crean los pipes de entrada y salida
	for(int i = 0; i < cantidad_discos; i++){
		pipe(pipes_entrada[i]);
		pipe(pipes_salida[i]);
	}

	char *args[] = {"vis", NULL};
	for(int i = 0; i < cantidad_discos; i++){
		if(fork() == 0){
			close(pipes_entrada[i][1]);
			close(pipes_salida[i][0]);
			dup2(pipes_entrada[i][0], STDIN_FILENO);
			dup2(pipes_salida[i][1], STDOUT_FILENO);
			execv(args[0], args);
		}
	}

	FILE *fp; // Variable que almacenará el archivo a leer
	FILE *fp_salida; // Variable que almacenará el archivo a escribir
	fp = fopen(nombre_archivo, "r");
	struct visibilidad *visibilidades = leerArchivo(fp); // Se lee el archivo y se guardan las visibilidades en un arreglo de structs
	int n = visibilidades->n; // Cantidad de visibilidades leídas del archivo
	float *radios = malloc(sizeof(float) * cantidad_discos); // Se reserva memoria para el arreglo de radios


	// Dado que el enunciado especifica que el radio de cada disco 
	// debe ser radio(k) = radio*k (asumiendo que k es un subindice en el lado izquierdo),
	// se calcula el radio de cada disco
	for(int i = 0; i < cantidad_discos; i++){
		radios[i] = ancho_disco*(i+1);
	}

	// Se escriben los datos de cada visibilidad en el pipe correspondiente
	for (int i = 0; i < cantidad_discos; i++){
		for (int j = 0; j < n; j++){
			if (calcularDistancia(visibilidades[j].pos_ejeU, visibilidades[j].pos_ejeV) <= radios[i]){
				write(pipes_entrada[i][1], &visibilidades[j].parte_real, SIZEDEFLOAT);
				write(pipes_entrada[i][1], &visibilidades[j].parte_imaginaria, SIZEDEFLOAT);
				write(pipes_entrada[i][1], &visibilidades[j].ruido, SIZEDEFLOAT);
			}
		}
	}

	// Se finaliza la lectura y se setean los valores de entrada a -1 (Fin de lectura)
	float fin = -1;
	for (int i = 0; i < cantidad_discos; i++){
		write(pipes_entrada[i][1], &fin, SIZEDEFLOAT);
		write(pipes_entrada[i][1], &fin, SIZEDEFLOAT);
		write(pipes_entrada[i][1], &fin, SIZEDEFLOAT);
	}

	// Se abre el archivo donde se escribirán las propiedades
	fp_salida = fopen(nombre_archivo_salida, "w");

	// Se leen los datos de cada visibilidad y se escriben en el archivo
	for (int i = 0; i < cantidad_discos; i++){
		read(pipes_salida[i][0], &pr, SIZEDEFLOAT);
		read(pipes_salida[i][0], &pi, SIZEDEFLOAT);
		read(pipes_salida[i][0], &ruido, SIZEDEFLOAT);
		read(pipes_salida[i][0], &potencia, SIZEDEFLOAT);
		read(pipes_salida[i][0], &cantidad, SIZEDEINT);
		read(pipes_salida[i][0], &pid_hijo, SIZEDEINT);
		
		
		fprintf(fp_salida, "Disco %d:\nMedia real: %f\nMedia imaginaria: %f\nPotencia: %f\nRuido total: %f\n", i+1, pr, pi, potencia, ruido);

		// Si se indicó que se deben imprimir los datos de cada visibilidad a través del print flag, se imprimen
		if (print_flag == 1){
			printf("Soy el hijo de pid %d, y procese %d visibilidades\n", pid_hijo, cantidad);
		}
	}

	// Se cierra el archivo utilizado para la escritura
	fclose(fp_salida);

	return 0;
}