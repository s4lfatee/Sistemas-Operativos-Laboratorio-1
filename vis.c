#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


int main(int argc, char *argv[]){
    float pr, pi, ruido; // Variables que leerán la parte real, imaginaria y ruido de una visibilidad
    int cantidad = 0; // Variable que almacena la cantidad de visibilidades leídas
    float promedio_real = 0; // Variable que almacena el promedio de las partes reales de todas las visibilidades
    float promedio_imaginario = 0; // Variable que almacena el promedio de las partes imaginarias de todas las visibilidades
    float ruido_total = 0; // Variable que almacena el promedio de los ruidos de todas las visibilidades
    float potencia = 0; // Variable que almacena la potencia de las visibilidades
    float real_total = 0; // Variable que almacena la suma de las partes reales de todas las visibilidades
    float imaginario_total = 0; // Variable que almacena la suma de las partes imaginarias de todas las visibilidades
    float real_total_cuadrado = 0; // Variable que almacena la suma de los cuadrados de las partes reales de todas las visibilidades
    float imaginario_total_cuadrado = 0; // Variable que almacena la suma de los cuadrados de las partes imaginarias de todas las visibilidades

    while(1){ // Loop que permite la lectura constante de visibilidades
        // Leemos la parte real, imaginaria y ruido de una visibilidad
        read(STDIN_FILENO, &pr, sizeof(float));
        read(STDIN_FILENO, &pi, sizeof(float));
        read(STDIN_FILENO, &ruido, sizeof(float));

        // Al terminar de leer se da este caso:
        if(pr == -1 && pi == -1 && ruido == -1){
            break;
        }

        // Se acumulan valores para el cálculo de las propiedades
        cantidad++;
        real_total += pr;
        imaginario_total += pi;
        ruido_total += ruido;

        real_total_cuadrado += pow(pr, 2);
        imaginario_total_cuadrado += pow(pi, 2);
    }

    promedio_real = real_total / cantidad;
    promedio_imaginario = imaginario_total / cantidad;

    potencia = sqrt(real_total_cuadrado + imaginario_total_cuadrado);

    // Se almacena el pid del proceso hijo
    int pid = getpid();

    // Se escribe de vuelta al proceso padre para que el proceso padre pueda mostrar las propiedades
    write(STDOUT_FILENO, &promedio_real, sizeof(float));
    write(STDOUT_FILENO, &promedio_imaginario, sizeof(float));
    write(STDOUT_FILENO, &ruido_total, sizeof(float));
    write(STDOUT_FILENO, &potencia, sizeof(float));
    write(STDOUT_FILENO, &cantidad, sizeof(int));
    write(STDOUT_FILENO, &pid, sizeof(int));

    return 0;
}