CC=gcc
FLAGS=-mtune="cortex-a53" -ggdb

main: file.o main.o
	$(CC) $(FLAGS) main.o file.o -o main
main.o: main.c
	$(CC) $(FLAGS) -c main.c

file.o: file.c
	$(CC) $(FLAGS) -c file.c


clean:
	rm *.o