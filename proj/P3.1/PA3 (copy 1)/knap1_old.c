//
// File name   : knap.c
// Author      : DaeGon
// Modified by : Sanjay and Wim 
// Date        : Sep 20
// Description : Dynamic Programming for the 0/1 knapsack
//               problem.  The entire table is saved.
//

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"


#define    MAX(x,y)   ((x)>(y) ? (x) : (y))
#define    table(i,j)    table[(i)*(C+1)+(j)]


//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------



//sub method to find value vector of 1/2 of the current problem
//needs to create an array of all the possible values for the capacity and a subset of the objects
//the solution array should be passed so that this method doesnt need to allocate any memory itself

//assume the results and objs arrays are of size capacity
//to know what subset of the objects we are working with, we need objs_start and objs_end

void solve_sub_kp(long objs_start, long objs_end, long* weights, long* profits, long* results, long capacity){

//results array is going to be our working array where we do all the computations 
//going row by row
//first row starts with wether or now we can take an object
//then we need to read the value of each index into memory as we compute it because we will overwrite it
//at each index we have 2 options: take or dont take 
//look at the current index value, and the currentIndex-(objectweight) index value
//to be able to do it in one array, we should start from the end?
//yes we need to start from the end and go to tjhe beggining so we havent already overwritten stuff

//printf(" NEW ITERATION NEW ITERATION NEW ITERATION \n");

//zero out the results array to make sure we start with a clean slate for this new set of objs
for(long i = 0; i<capacity;i++){
results[i] = 0;
}


//now for the actual loop
//nested loops to go to the end of the objects, and another to compute each row
//take note that objs_start is the first object, and objs_end is one after the last object
for(long object = objs_start; object<objs_end; object++){

	//printf("object: %d \n", object); 
	long current_profit = profits[object];
	long current_weight = weights[object];
	
	//printf("   current_profit %d \n", current_profit); 
	//printf("   current_weight %d \n", current_weight); 

		//this loop iterates backwards over the row elements
		//row index directly maps to capacity available, and 0 is a valid input
		for(long row_index = capacity; row_index >= 0; row_index--){

		//printf("           row index %d \n", row_index);
		//check to make sure object fits to not try to access array out of range
		if(row_index < current_weight);
		//update the element in the row to be the max of taking the object and not taking it
		else{
		long check1 = results[row_index];
		long check2 = results[row_index-current_weight]+current_profit;
		//printf("           assigning value %d \n", MAX(check1,check2));
		results[row_index] = MAX(check1,check2);
		}
		}


}
//in theory, at the end of this loop the results array should be filled with final profits for each
//weight considering only this set of objects
return;
}

//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------


//this function will find the optimal capacity break given two results vectors 
//I dont actually need to know the max profit just the index where it occurrs?
//probably

long find_optimal_capacity_helper(long* results1, long*results2, long capacity){

long maxprofit = results2[capacity-1];
long profitIndex = 0;





	for(int i = 0; i<=capacity; i++){
	
	//printf("	res1 %d \n", results1[i]);
	//printf("	res2 %d \n", results2[i]);
	long profit1 = results1[i];
	long profit2 = results2[(capacity-1)-i];
	long totalprofit = profit1 + profit2;
	if(totalprofit>maxprofit){
		printf("entering if statement totalprofit is %d \n", totalprofit);
		maxprofit = totalprofit;
		profitIndex = i;
		}
	
	
	}



printf("maxprofit %d \n", maxprofit);
return profitIndex;
}

//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------

//this function exists to do what both the above functions due with only 1 function call
//takes a ton of args, and returns the index that is needed to split up array
long find_optimal_capacity(long objs_start, long objs_end, long* weights, long* profits, long* results1, long* results2, long capacity)
{
long objs_mid = ((objs_end - objs_start)/2) + objs_start;

solve_sub_kp(objs_start, objs_mid, weights, profits, results1, capacity);
solve_sub_kp(objs_mid, objs_end, weights, profits, results2, capacity);
long index = find_optimal_capacity_helper(results1, results2, capacity);
return index;
}

//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------


//this method needs to take in the index that the split happens at, and return a pointer that will be
//used at the start of the new array for the second recursive call
long* get_new_array_pointer( long* results, long split_point){
return results+split_point+1;
}


long* get_new_array_pointer_simple(long capacity){

long* results_new = (long *)malloc((capacity+1)*sizeof(long));

return results_new;

}








//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------


//this function needs to get the solution path
//it needs to be recursive and construct the solution path as it goes
//each sub problem should return a solution vector for its sub problem
//this might allocate a fuckton of memory if Im not careful
//maybe the solutions vector can be contructed in place
//I always know the size of it from the size of weights and profits
//the array can have 0 or 1 to represent take or not take
//each obj at the base case can decide to take or not take
//solutions will be my solutions vector
//the method will assume that solutions comes in zeroed out/ not with weird data in it
void solve_kp(long objs_start, long objs_end, long* weights, long* profits, long* results1, long* results2, long capacity, int* solutions)
{
//first check if we are at the base case
//if we are down to one object
//and we have the capacity left to take it
//update the solutions array to show that we want to take that object

printf("objs sart, end, capacity %d %d %d \n", objs_start, objs_end, capacity);

if(objs_start == objs_end-1){
	//printf("if statement has been entered. Remaining capacity: %d \n", capacity);
	//printf("weight of object %d \n", weights[objs_start]);
	if(capacity >= weights[objs_start]) 
	{
		//printf("	inner if. Remaining capacity: %d \n", capacity);
		printf("	choosing object %d with weight %d \n", objs_start, weights[objs_start]);		
		solutions[objs_start] = 1;
	}
	return;
}
//then if we are not at the base case find out how to split into recursive versions
// half calls go with index and c-index


long index = find_optimal_capacity(objs_start, objs_end, weights, profits, results1, results2, capacity);
printf("	index break is %d \n", index);
// make new smaller arrays that are going to be passed on
/*
long* results1_call1 = results1;
long* results2_call1 = results2;
long* results1_call2 = get_new_array_pointer(results1, index);
long* results2_call2 = get_new_array_pointer(results2, index);
*/
long capacity_call1 = index;
long capacity_call2 = capacity-index;

long* results1_call1 = get_new_array_pointer_simple(capacity_call1);
long* results2_call1 = get_new_array_pointer_simple(capacity_call1);
long* results1_call2 = get_new_array_pointer_simple(capacity_call2);
long* results2_call2 = get_new_array_pointer_simple(capacity_call2);



long objs_mid = ((objs_end + objs_start)/2);

//now I need to recurse so that the end object is exclusive

solve_kp(objs_start, objs_mid, weights, profits, results1_call1, results2_call1, capacity_call1, solutions);
solve_kp(objs_mid, objs_end, weights, profits, results1_call2, results2_call2, capacity_call2, solutions);

return;

}
//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------

int printArray(long* array, long length){

for(int i = 0; i<length;i++){
printf(" %d ", array[i]);
}
printf(" \n ");
return 0;
}

int printArray_int(int* array, long length){

for(int i = 0; i<length;i++){
printf(" %d", array[i]);
}
printf(" \n ");
return 0;
}

long calculateValue(int* solutions, long* profits, long capacity){
long max = 0;
for(long i = 0; i<=capacity;i++){
if(solutions[i] == 1) max += profits[i];
}
return max;
}

//---------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------



int main(int argc, char **argv) {

   FILE   *fp;
   long    N, C;                   // # of objects, capacity 
   long    *weights, *profits;     // weights and profits
   int    verbose,count;

   // Temp variables
   long    i, j, size;

   // Time
   double time;

   // Read input file (# of objects, capacity, (per line) weight and profit )
   if ( argc > 1 ) {
      fp = fopen(argv[1], "r"); 
      if ( fp == NULL) {
         printf("[ERROR] : Failed to read file named '%s'.\n", argv[1]);
         exit(1);
      }
   } else {
      printf("USAGE : %s [filename].\n", argv[0]);
      exit(1);
   }

   if (argc > 2) verbose = atoi(argv[2]); else verbose = 0;

   fscanf(fp, "%ld %ld", &N, &C);
   printf("The number of objects is %d, and the capacity is %d.\n", N, C);

   size    = N * sizeof(long);
   weights = (long *)malloc(size);
   profits = (long *)malloc(size);

   if ( weights == NULL || profits == NULL ) {
      printf("[ERROR] : Failed to allocate memory for weights/profits.\n");
      exit(1);
   }

   for ( i=0 ; i < N ; i++ ) {
      count = fscanf(fp, "%ld %ld", &(weights[i]), &(profits[i]));
      if ( count != 2 ) {
         printf("[ERROR] : Input file is not well formatted.\n");
         exit(1);
      }
   }

   fclose(fp);
//----------------------------------------------------------------
//
//N is number of objects, and C is capacity
//
//----------------------------------------------------------------
long* results1 = (long *)malloc((C+1)*sizeof(long));
long* results2 = (long *)malloc((C+1)*sizeof(long));

solve_sub_kp(0, N/2, weights, profits, results1, C);
solve_sub_kp((N/2), N, weights, profits, results2, C);


/*
printArray(weights,N);
printArray(profits,N);
printf( "sub1 range: %d %d \n", 0, N/2);
printf( "sub2 range: %d %d \n", N/2, N);
*/
//printArray(results1,C+1);
//printArray(results2,C+1);

long* prof_p1 = results1;
long* prof_p2 = results2;

long index = find_optimal_capacity_helper(prof_p1, prof_p2, C);

long index2 = find_optimal_capacity(0, N, weights, profits, results1, results2, C);

printf("index %d \n", index);
printf("index2 %d \n", index2);
printf("first value %d \n", prof_p1[index]);
printf("second value %d \n", prof_p2[C-index]);
printf("total %d \n", prof_p2[C-index]+prof_p1[index]);

int* solutions = (int *)calloc(N, sizeof(int));

solve_kp(0, N, weights, profits, results1, results2, C, solutions);

printArray_int(solutions, N);

long result = calculateValue(solutions,profits,C);
printf(" %d \n ", result);

   return 0;
}
