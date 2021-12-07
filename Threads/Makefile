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

mutex_sema: mutex_sema.o
	$(CC) $(FLAGS) mutex_sema.o $(LIBS) -o ../bin/mutex_sema

mutex_sema.o: semaphores/mutex_sema.c
	$(CC) $(FLAGS) -c semaphores/mutex_sema.c  -o mutex_sema.o

#signalling_sema: signalling_sema.o
#	$(CC) $(FLAGS) signalling_sema.o $(LIBS) -o ../bin/signalling_sema

#signalling_sema.o: semaphores/signalling_sema.c
#	$(CC) $(FLAGS) -c semaphores/signalling_sema.c  -o signalling_sema.o

calc: calc.o
	$(CC) $(FLAGS) calc.o $(LIBS) -o ../bin/calc

calc.o: semaphores/calc.c
	$(CC) $(FLAGS) -c semaphores/calc.c  -o calc.o



clean:
	rm *.o *.txt