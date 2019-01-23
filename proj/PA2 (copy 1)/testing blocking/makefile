CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3 
MATHFLAGS = -lm
EXEC = test

all: $(EXEC)

test: test.c $(OBJS)
	$(CC) $(SEQFLAGS)  -o $@ $< $(OBJS) $(MATHFLAGS)
timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

PA2.tar: sieve.c sieve1.c sieve2.c sieve3.c sieve4.c report.pdf makefile
	tar cvf PA2.tar sieve.c sieve1.c sieve2.c sieve3.c sieve4.c report.pdf makefile
