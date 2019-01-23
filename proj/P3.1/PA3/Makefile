
CC = gcc
OBJS = timer.o
FLAGS = -fopenmp -O3 -g
SEQFLAGS = -O3 -g

EXEC = knapSeq knap1 knap2 knap3

all: $(EXEC)

knapSeq: knap.c timer.o
	$(CC)  $(SEQFLAGS) -o knapSeq knap.c $(OBJS) 

knap1: knap1.c timer.o
	$(CC)  $(SEQFLAGS) -o knap1 knap1.c $(OBJS) 

knap2: knap2.c timer.o
	$(CC)  $(FLAGS) -o knap2 knap2.c $(OBJS) 

knap3: knap3.c timer.o
	$(CC)  $(FLAGS) -o knap3 knap3.c $(OBJS) 

timer.o: timer.c
	$(CC) -o $@ -c timer.c

clean:
	rm -f $(EXEC) $(OBJS) knap1

tar: Makefile report.pdf knap1.c knap2.c knap3.c
	tar cvf PA3.tar Makefile report.pdf knap1.c knap2.c knap3.c
