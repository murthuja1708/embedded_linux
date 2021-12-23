CC=gcc
FLAGS=-g
LIBS=-lpthread
EXLIBS=-lrt

# Question1

prob1: proc_receiver proc_sender

proc_receiver: prob1/proc_receiver.c
	$(CC) $(FLAGS) $< $(LIBS) $(EXLIBS) -o prob1/$@

proc_sender: prob1/proc_sender.c prob1/str_read.c
	$(CC) $(FLAGS) prob1/proc_sender.c prob1/str_read.c $(LIBS) $(EXLIBS) -o prob1/$@

# Question2

prob2: producer1 consumer1

producer1:	prob2/producer1.c
	$(CC) $(FLAGS) $< $(LIBS) $(EXLIBS) -o prob2/$@

consumer1:	prob2/consumer1.c
	$(CC) $(FLAGS) $< $(LIBS) $(EXLIBS) -o prob2/$@

# Question3

prob3: prob3/question3.c
	$(CC) $(FLAGS) $< $(LIBS) $(EXLIBS) -o prob3/$@


# Question4


prob4: process1 process2

process1:	prob4/process1.c
	$(CC) $(FLAGS) $< $(LIBS) $(EXLIBS) -o prob4/$@

process2:	prob4/process2.c prob4/str_read.c
	$(CC) $(FLAGS) prob4/process2.c prob4/str_read.c $(LIBS) $(EXLIBS) -o prob4/$@


