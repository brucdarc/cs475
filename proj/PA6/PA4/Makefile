OBJS = timer.o
H_FILE = timer.h
OMPFLAGS = -O3 -fopenmp
MPIFLAGS = -O3 
MATHFLAG = -O3
EXEC = jac jacMPI jacOMP

all: $(EXEC)

jac: jac.c $(OBJS) $(H_FILE)
	gcc -O3 -o $@ jac.c $(OBJS) $(MATHFLAG)

jacOMP: jacOMP.c $(OBJS) $(H_FILE)
	gcc -O3 -o $@ jacOMP.c $(OBJS) $(OMPFLAGS)

jacMPI: jacMPI.c $(OBJS) $(H_FILE)
	mpicc -O3 -o $@ jacMPI.c $(OBJS) $(MATHFLAG)

clean:
	rm -f $(EXEC)

tar:
	tar cvf PA6.tar Makefile jacOMP.c jacMPI.c report.pdf
