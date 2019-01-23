
CC = gcc
OBJS = timer.o
FLAGS = -fopenmp -O3
SEQFLAGS = -O3 -g

EXEC = knapSeq knapSeq1

all: $(EXEC)

knapSeq: knap.c timer.o
	$(CC)  $(SEQFLAGS) -o knapSeq knap.c $(OBJS) 

knapSeq1: knap1.c timer.o
	$(CC)  $(SEQFLAGS) -o knapSeq1 knap1.c $(OBJS) 

timer.o: timer.c
	$(CC) -o $@ -c timer.c

clean:
	rm -f $(EXEC) $(OBJS) knap1

tar: Makefile report.pdf knap1.c knap2.c knap3.c
	tar cvf PA3.tar Makefile report.pdf knap1.c knap2.c knap3.c
