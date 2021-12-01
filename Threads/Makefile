CC=gcc
FLAGS=-ggdb
LIBS=-lpthread

thread: thread.o
	$(CC) $(FLAGS) thread.o $(LIBS) -o ../bin/thread

thread.o: hello_thread.c
	$(CC) $(FLAGS) -c hello_thread.c  -o thread.o


clean:
	rm *.o