FLAGS = -g

all: main

main: lab1.c funciones.o
	gcc $(FLAGS) funciones.o lab1.c -o main -lm

funciones.o: funciones.c funciones.h
	gcc $(FLAGS) -c funciones.c

clean:
	rm -f *.o main