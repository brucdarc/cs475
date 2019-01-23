/*
 * jacobi.c
 * WimBo
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "mpi.h"

int main(int argc, char **argv) {
    int my_id, next_id;	/* process id-s */
    int p;		/* number of processes */
    char* message;	/* storage for the message */
    int max_msgs, msg_size;
    MPI_Status status;	/* return status for receive */


    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &my_id );
    MPI_Comm_size( MPI_COMM_WORLD, &p );



   int     n;
   int     t;
   int     m = 2000;
   int     b = 5;
   double  *prev, *cur, *buffer;

   // Timer
   double  time;

   // temporary variables
   int i,j;
   int v = 0; //verbose
   double  *temp;

   // Check commandline args.
   if ( argc > 1 ) {
      n = atoi(argv[1]);
   } else {
      printf("Usage : %s [N]\n", argv[0]);
      exit(1);
   }
   if ( argc > 2 ) {
      m = atoi(argv[2]);
   }
   if ( argc > 3 ) {
      b = atoi(argv[3]);
      //printf("%d \n", b);
   }

   if ( argc > 4 ) {
      v = 1;
   }

   // Memory allocation for data array.
   prev  = (double *) malloc( sizeof(double) * (n/p+2*b+1));
   cur   = (double *) malloc( sizeof(double) * (n/p+2*b+1));
   if ( prev == NULL || cur == NULL ) {
      printf("[ERROR] : Fail to allocate memory.\n");
      exit(1);
   }

   // Initialization
   
   int start = (n/p) * my_id - b; 
   int length = n/p + 2*b;
   for ( i=start ; i <= start + (n/p + 2*b) ; i++ ) {
         prev[i-start] = i;
      }



  

   cur[0]  = start;
   cur[length]  = start + length;
   if(my_id == p-1) cur[length-b-1] = start + length -b-1;



   initialize_timer();
   start_timer();


   t = 0;


   if(p==1){


   while ( t < m) {
      for ( i=1 ; i < n-1 ; i++ ) {
            cur[i] = (prev[i-1]+prev[i]+prev[i+1])/3;
       }
      temp = prev;
      prev = cur;
      cur  = temp;
      t++;
   }

   }

   if(my_id == 0){
	   while ( t < m) {



	   for(int placeholder = t; t<m && t-placeholder < b; t++){
	      for ( i=1+b ; i <= n/p+2*b-1 ; i++ ) {
		    cur[i] = (prev[i-1]+prev[i]+prev[i+1])/3;
	       }
	
	      temp = prev;
	      prev = cur;
	      cur  = temp;
	   }


	    
	    MPI_Send(prev + n/p, b, MPI_DOUBLE, my_id+1, 0, MPI_COMM_WORLD);
	    MPI_Recv(prev + n/p + b, b, MPI_DOUBLE, my_id+1, 1, MPI_COMM_WORLD, &status);   
	

 

	   }
    }

   else if(my_id == p-1){
	   while ( t < m) {



	   for(int placeholder = t; t<m && t-placeholder < b; t++){
	      for ( i=1 ; i < n/p+b-1 ; i++ ) {
		    cur[i] = (prev[i-1]+prev[i]+prev[i+1])/3;
	       }


			
	      temp = prev;
	      prev = cur;
	      cur  = temp;
	   }


	    MPI_Recv(prev, b, MPI_DOUBLE, my_id-1, 0, MPI_COMM_WORLD, &status); 
	    MPI_Send(prev+b, b, MPI_DOUBLE, my_id-1, 1, MPI_COMM_WORLD);
		 



	   }
    }


   else{
	   while ( t < m) {



	   for(int placeholder = t; t<m && t-placeholder < b; t++){
	      for ( i=1 ; i <= n/p+2*b-1 ; i++ ) {
		    cur[i] = (prev[i-1]+prev[i]+prev[i+1])/3;
	       }

            
    
			
	      temp = prev;
	      prev = cur;
	      cur  = temp;
	   }

	    MPI_Send(prev + n/p, b, MPI_DOUBLE, my_id+1, 0, MPI_COMM_WORLD);

	    MPI_Recv(prev, b, MPI_DOUBLE, my_id-1, 0, MPI_COMM_WORLD, &status);	 

	    MPI_Send(prev+b, b, MPI_DOUBLE, my_id-1, 1, MPI_COMM_WORLD);
	    MPI_Recv(prev + n/p+b, b, MPI_DOUBLE, my_id+1, 1, MPI_COMM_WORLD, &status); 



  
	    
		 




	   }
    }



   stop_timer();
   time = elapsed_time();

   if(my_id == 0){
	buffer  = (double *) malloc( sizeof(double) * (n));
   }

   if(p!=1){
	   MPI_Gather(prev+b, n/p, MPI_DOUBLE, buffer, n/p, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	   prev = buffer;
   }



   if(my_id == 0){
	   if(v){
	     for(i=0;i<n;i++) printf("%f ",prev[i]);
	     printf("\n");
	   }
	   else
	     printf("first, mid, last: %f %f %f\n",prev[0], prev[n/2-1], prev[n-1]);
	     
	   printf("Data size : %d  , #iterations : %d , time : %lf sec\n", n, t, time);

   }
   MPI_Finalize();
}



