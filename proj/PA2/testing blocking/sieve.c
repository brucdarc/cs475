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



//----------------------------------------------------------------------------------
//
//                    MAIN 
//
//----------------------------------------------------------------------------------

int main(int argc, char **argv) {

   long NBODIES = 100;
   long original_N =100;
   char *OUT;

   long   size;
   long   curr;
   long   i, j,n;
   long   count;

   /* Time */

   double time;
   long BLOCK;
   if ( argc > 1 ) 
	{
	 NBODIES  = atoi(argv[1]);
	}
   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (NBODIES+1)*sizeof(char);
   OUT = (char *)malloc(size);


   initialize_timer ();
   start_timer();
int useless = 0;

for (int body1 = 0; body1 < NBODIES; body1 ++) {
   for (int body2=0; body2 < NBODIES; body2++) {
     useless += body1 + OUT[body2];
   }
}
   stop_timer();
   time=elapsed_time ();


   printf("elapsed time = %lf (sec)\n", time);
   free(OUT);
   return 0;
}


