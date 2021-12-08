CC=gcc
FLAGS=-ggdb
LIBS=-lrt -lpthread

# named pipes build

fifo: calc print

calc: calc.o named_pipes_main.o
	$(CC) $(FLAGS) calc.o named_pipes_main.o -o ../bin/calc_p2

print: print.o
	$(CC) $(FLAGS) print.o -o ../bin/display_p1

named_pipes_main.o: named\ pipes/main.c
	$(CC) $(FLAGS) -c named\ pipes/main.c -o named_pipes_main.o

calc.o: named\ pipes/calc.c
	$(CC) $(FLAGS) -c named\ pipes/calc.c -o calc.o

print.o: named\ pipes/print.c
	$(CC) $(FLAGS) -c named\ pipes/print.c -o print.o

#fork

fork: fork.o
	gcc fork.o -o ../bin/shell

fork.o: fork.c
	gcc -c fork.c -o fork.o

#pipes

arith_pipes: arith_pipes.o
	gcc arith_pipes.o -o ../bin/arith_pipes

arith_pipes.o: pipes/pipes.c
	gcc -c pipes/pipes.c -o arith_pipes.o


#shared memories

shared_memories: process_1 process_2

process_1:	shared_memories/process_1.c
	$(CC) $(FLAGS) $< $(LIBS) -o ../bin/process_1

process_2:	shared_memories/process_2.c
	$(CC) $(FLAGS) $< $(LIBS) -o ../bin/process_2

message_queues: sender receiver

sender:	message_queues/sender.c
	$(CC) $(FLAGS) $< $(LIBS) -o ../bin/$@

receiver:	message_queues/receiver.c
	$(CC) $(FLAGS) $< $(LIBS) -o ../bin/$@


clean:
	rm *.o ../bin/process_*