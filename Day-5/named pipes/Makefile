CC=gcc
FLAGS=-ggdb

all: calc print

calc: calc.o main.o
	$(CC) $(FLAGS) calc.o main.o -o ../../bin/calc_p2

print: print.o
	$(CC) $(FLAGS) print.o -o ../../bin/display_p1

main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o

calc.o: calc.c
	$(CC) $(FLAGS) -c calc.c -o calc.o

print.o: print.c
	$(CC) $(FLAGS) -c print.c -o print.o


clean:
	rm *.o