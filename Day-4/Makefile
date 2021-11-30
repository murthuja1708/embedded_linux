CC=gcc
FLAGS=-ggdb


_cp: file.o main.o
	$(CC) $(FLAGS) file.o main.o -o ../bin/_cp
main.o: main.c
	$(CC) $(FLAGS) -c main.c

file.o: file.c
	$(CC) $(FLAGS) -c file.c -o file.o


clean:
	rm *.o