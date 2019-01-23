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

//manually fix marks near square root
void fix_near_sqrt(char* mark, long size, long* primes, int psize)
{
//printf(" %d \n ", size*2+1);
//printf(" %f \n ", sqrt(size*2+1));
//printf("fixing around index %d \n",sqrt(size*2+1)/2);
float fsqrt = sqrt(size*2+1)/2;
long sqrt_index = (long)fsqrt;
//printf(" %f \n ", fsqrt);
//printf(" %d \n ", sqrt_index);
for(long index = sqrt_index-2;index<sqrt_index+2;index++)
{
	for(int pindex = 0; pindex<psize;pindex++)
	{
	//printf("checking number %d  value is %d  prime is %d  \n ", index*2+1, mark[index], primes[pindex] );
	if(primes[pindex] == index*2+1) mark[index] = 0;
	else if((index*2+1)%primes[pindex] == 0) mark[index] = 1;

	}
}


}





long min(long a, long b){
if(a>b) return a;
else return b;
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
		//printf("number %d mark is %d \n", i*2+1, mark[i]);
		if(mark[i] == 0){
		result[count] = i*2+1;
		//printf("%d ", result[count]);
		count++;
		}//if statement close

		}//for loop close
	//printf("\n");
	return result;
}


long FMIB(int start, long prime, long block_size)
{
start = start;

long prime_sq = prime * prime;
//if the square is halfway through start at it, it is gauranteed to be odd
if(prime_sq > start && prime_sq <= start+block_size) return prime_sq;
//if the square is above the block, skip the block by starting at the end
if(prime_sq > start + block_size) return start+block_size;

start = start-1;

//int result = start + (prime - start%prime);
//return result;
//for(int i = start; i<start+2*prime;i++) if(i%prime==0 && i%2!=0) return i;
long result = start + (prime - start%prime);
if(result%2 ==0) result = result+prime;
return result;
}

//----------------------------------------------------------------------------------
//
//                    MAIN 
//
//----------------------------------------------------------------------------------

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
   long block_size;
   if ( argc > 2 ) 
	{
	 original_N  = atoi(argv[1]);
	 N = original_N/2;
	if(original_N%2 == 0) N--;
	block_size = atoi(argv[2]);
	}
   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (N+1)*sizeof(char);
   mark = (char *)malloc(size);

   for (i=0; i<=N; i=i+1){
     mark[i]=0;
   }


   curr=3;       /*first prime*/
   while (curr<=sqrt(N*2+1)) {
	//printf("curr: %d \n",curr);

//only go to sqrt n because that is the first block
//FIRST BLOCK
   for (int i=curr*curr; i<=sqrt(N*2+1)+1; i = i+2*curr)
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
   
   //printf("%d \n", start);

   initialize_timer ();
   start_timer();


//printf("starting block %d \n", start);
	


for(int start = start_second_block+2; start<N*2+1; start += block_size)
{

	for(long pindex = 0; pindex<numprimes; pindex++)
	{
		//printf("doing primeindex %d \n",pindex); 
		

		long prime = primes[pindex];
	
		//printf("doing prime %d \n", prime);
		for(int index=FMIB(start,prime,block_size);index<fmin(start+block_size,N*2+2); index += 2*prime)
			{
			//printf("inner index %d \n",index);
					
				{
				//prime = prime[index];
				mark[index/2]=1;
				}
				}
			
	}
}

   stop_timer();
   time=elapsed_time ();

//printMarkArray(mark,N+1);

//manually fix primes near sqrt
fix_near_sqrt(mark, N, primes, psize);
















   

   /*number of primes*/
   count = 2;
   for(i = 2; i <=N; i++){
        if(mark[i] == 0) {
        	//if(i<31700/2) printf("\t prime %ld   %d  \n",i*2+1,i);
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


