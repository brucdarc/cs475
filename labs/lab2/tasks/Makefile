CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
DEBUGFLAG = -DDEBUG
SEQFLAGS = -O3 -lm

EXEC = Merge_sort Merge_sort_debug Merge_sort_par

all: $(EXEC)

Merge_sort: Merge_sort.c $(OBJS)
	$(CC) $(SEQFLAGS)  -o $@ $< $(OBJS)

Merge_sort_par: Merge_sort.c $(OBJS)
	$(CC) $(FLAGS)  -o $@ $< $(OBJS)

Merge_sort_debug:Merge_sort.c $(OBJS)
	$(CC) $(SEQFLAGS) $(DEBUGFLAG)  -o $@ $< $(OBJS)

timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)
