/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve.c
// Author    : Nissa Osheim
// Date      : 2010/19/10
// Desc      : Finds the primes up to N
//
// updated Wim Bohm
/////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"


void mark(int index,char *marked_array){
if(index%2==0) return;

return;

}

void printArray(long* array, int size){
//printf("size inside printArray %d ", size);
printf("starting printArray  \n");
	for(int i = 0; i<size; i++)
	{
	printf(" %d ", array[i]);
	
	}
printf("\n");

}

void printMarkArray(char* array, int size){
//printf("size inside printArray %d ", size);
int c = 1;
printf("starting printArray  \n");
	for(int i = 0; i<size; i++)
	{
	if(array[i] == 0)
	printf(" %d:%d ", c, array[i]);
	c++;
	//printf(" %d:%d ", c, 1);
	c++;
	}
printf("\n");

}

int getSizePrimes(char* mark, long N){
	//printf("N is %d \n", N); 
	//count the primes to figure out how big the array needs to be
	// sqrt(2*n+1)/2 is the same as sqrt(N/20
	int count = 0;
	for(int i = 1; i<sqrt(2*N+1)/2; i++){
	//printf("mark of i is %d \n", mark[i]);
	if(mark[i] == 0){ count++;} //printf("incrementing count i is %d \n", i);}
	}
	//printf("count after first loop is %d \n", count);
	//allocate space for the array
	return count;
}

long* getPrimes(char* mark, long N, int count){
	//printf("N is %d \n", N); 

	int size = count*sizeof(long);

	//printf("size is %d \n", size);
	//printf("size of long is %d \n", sizeof(long));
	
	count = 0;  

	long* result = malloc(size);
	
		for(int i = 1; i<sqrt(2*N+1)/2; i++){
		//printf("count %d \n", i);
		if(mark[i] == 0){
		result[count] = i*2+1;
		//printf("%d ", result[count]);
		count++;
		}//if statement close

		}//for loop close
	//printf("\n");
	return result;
}


long FMIB(int start, long prime)
{
//int result = start + (prime - start%prime);
//return result;
for(int i = start; i<start+2*prime;i++) if(i%prime==0 && i%2!=0) return i;
}


int main(int argc, char **argv) {

   long N  = 100;
   long original_N =100;
   char *mark;

   long   size;
   long   curr;
   long   i, j,n;
   long   count;

   /* Time */

   double time;

   if ( argc > 1 ) 
	{
	 original_N  = atoi(argv[1]);
	 N = original_N/2;
	if(original_N%2 == 0) N--;
	}
   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (N+1)*sizeof(char);
   mark = (char *)malloc(size);
#pragma omp parallel for
   for (i=0; i<=N; i=i+1){
     mark[i]=0;
   }


   curr=3;       /*first prime*/
   while (curr<=sqrt(N*2+1)) {
	//printf("curr: %d \n",curr);

//only go to sqrt n because that is the first block
//FIRST BLOCK
long end = sqrt(N*2+1);
#pragma omp parallel for
   for (long i=curr*curr; i<=end; i = i+2*curr)
     if (i%curr == 0) mark[i/2]=1;
   while (mark[++curr/2]); if(curr%2 ==0) curr++; /* do nothing */
   /* now index has the first unmarked number, so ... */
   }

   //printf("N is %d \n", N);
   int psize = getSizePrimes(mark,N); 
   long* primes = getPrimes(mark,N,psize);
   //printArray(primes,psize);
   int numprimes = psize;
   //printf("size %d \n", psize);
   //printf("numprimes %d \n", numprimes);
   /* stop timer */


   int start_second_block = sqrt(N*2+1);
   int block_size = 10000;
   //printf("%d \n", start);
#pragma omp parallel for
for(int start = start_second_block+2; start<N*2+1; start += block_size)
{
	//printf("starting block %d \n", start);
	for(long pindex = 0; pindex<numprimes; pindex++)
	{
		//printf("doing primeindex %d \n",pindex); 
		

		long prime = primes[pindex];
		//printf("doing prime %d \n", prime);
		for(int index=FMIB(start,prime);index<fmin(start+block_size,N*2+2); index += 2*prime)
			{
			//printf("inner index %d \n",index);
					
				if (index%prime == 0){
				
				mark[index/2]=1;
				}
				}
			
	}
}

//printMarkArray(mark,N+1);

















   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 2;
   for(i = 2; i <=N; i++){
        if(mark[i] == 0) {
        	//printf("\t prime %ld   %d  \n",i*2+1,i);
        	++count;
        }

   }
   
   int extra = 0;
   if(original_N%2==0) extra = 1;
   printf("There are %ld primes less than or equal to %ld\n", count, N*2+1 + extra);
   /* print results */
   printf("First three primes:");
   j = 1;
   printf("%d ", 2);
   for ( i=3 ; i <= N && j < 3; i+=2 ) {
      if (mark[i/2]==0){
            printf("%ld ", i);

            ++j;
      }
   }
   printf("\n");

   printf("Last three primes:");
   j = 0;
   n=N;
   for (i = n; i > 1 && j < 3; i--){
     if (mark[i]==0){
        printf("%ld ", i*2+1);
        j++;
     }
   }
   printf("\n");


   printf("elapsed time = %lf (sec)\n", time);
   free(primes);
   free(mark);
   return 0;
}


