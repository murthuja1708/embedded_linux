CC=gcc
FLAGS=-ggdb
LIBS=-lpthread

#lock and wait
mutexes_pt1: mutexes_pt1.o
	$(CC) $(FLAGS) mutexes_pt1.o $(LIBS) -o ../bin/mutexes

mutexes_pt1.o: mutexes/mutexes_pt1.c
	$(CC) $(FLAGS) -c mutexes/mutexes_pt1.c  -o mutexes_pt1.o

#try_lock,timed_lock and also different types of mutextes
mutexes_pt2: mutexes_pt2.o
	$(CC) $(FLAGS) mutexes_pt2.o $(LIBS) -o ../bin/mutexes

mutexes_pt2.o: mutexes/mutexes_pt2.c
	$(CC) $(FLAGS) -c mutexes/mutexes_pt2.c  -o mutexes_pt2.o

#mutex semaphores

mutex_sema: mutex_sema.o
	$(CC) $(FLAGS) mutex_sema.o $(LIBS) -o ../bin/mutex_sema

mutex_sema.o: semaphores/mutex_sema.c
	$(CC) $(FLAGS) -c semaphores/mutex_sema.c  -o mutex_sema.o

#signalling semaphores

calc: calc.o
	$(CC) $(FLAGS) calc.o $(LIBS) -o ../bin/calc

calc.o: semaphores/calc.c
	$(CC) $(FLAGS) -c semaphores/calc.c  -o calc.o

#counting semaphores

resource_mgmt: resource_mgmt.o
	$(CC) $(FLAGS) resource_mgmt.o $(LIBS) -o ../bin/resource_mgmt

resource_mgmt.o: semaphores/resource_mgmt.c
	$(CC) $(FLAGS) -c semaphores/resource_mgmt.c  -o resource_mgmt.o

#barriers

barrier: barriers/barrier.c
	$(CC) $(FLAGS) $< $(LIBS) -o ../bin/$@


clean:
	rm *.o *.txt