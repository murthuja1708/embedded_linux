CC=gcc
FLAGS=-ggdb
CFLAGS=-mtune="cortex-a53"

main: file.o main.o
	$(CC) $(FLAGS) main.o file.o -o main
main.o: main.c
	$(CC) $(FLAGS) -c main.c

file.o: read_file.c
	$(CC) $(FLAGS) -c read_file.c -o file.o


clean:
	rm *.o