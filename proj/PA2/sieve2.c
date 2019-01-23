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
   #pragma omp parallel for
   for (i=curr*curr; i<=N*2+1; i = i+2*curr)
     mark[i/2]=1;
   while (mark[++curr/2]); if(curr%2 ==0) curr++; /* do nothing */
   /* now index has the first unmarked number, so ... */
   }

   /* stop timer */
   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 2;
   for(i = 2; i <=N; i++){
        if(mark[i] == 0) {
        	 // printf("\t prime %ld  \n",i*2+1);
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

   free(mark);
   return 0;
}


