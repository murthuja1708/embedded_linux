CC=gcc
FLAGS=-ggdb
LIBS=-lpthread

thread: thread.o
	$(CC) $(FLAGS) thread.o $(LIBS) -o ../bin/thread

thread.o: hello_thread.c
	$(CC) $(FLAGS) -c hello_thread.c  -o thread.o

mutexes_pt1: mutexes_pt1.o
	$(CC) $(FLAGS) mutexes_pt1.o $(LIBS) -o ../bin/mutexes

mutexes_pt1.o: mutexes/mutexes_pt1.c
	$(CC) $(FLAGS) -c mutexes/mutexes_pt1.c  -o mutexes_pt1.o

mutexes_pt2: mutexes_pt2.o
	$(CC) $(FLAGS) mutexes_pt2.o $(LIBS) -o ../bin/mutexes

mutexes_pt2.o: mutexes/mutexes_pt2.c
	$(CC) $(FLAGS) -c mutexes/mutexes_pt2.c  -o mutexes_pt2.o

sema: sema.o
	$(CC) $(FLAGS) sema.o $(LIBS) -o ../bin/sema

sema.o: semaphores/sema_basics.c
	$(CC) $(FLAGS) -c semaphores/sema_basics.c  -o sema.o

clean:
	rm *.o *.txt