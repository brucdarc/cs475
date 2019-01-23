#include <stdio.h>
#include "MM2chainKernel.h"




__global__ void multiply(const float* A, float* partial_mult ){

int block = blockIdx.x;
int thread = threadIdx.x;


/*
if(thread == 1){
for( int i = 0; i<240; i++){
printf("%f\n", *(A+i));
}
}*/

/*
if(block==32 && thread == 1) {
for( int i = 0; i<240; i++){
printf("%f\n",  *(A+i+31*240+((BLOCK_SIZE)*(blockIdx.x))));
}
}*/

__shared__ float shared_A[B*C*4];


const float* AStart = A + ((B)*(blockIdx.x)*C*4);
//if(threadIdx.x == 1) printf("A %p Astart %p  \n ", A, AStart);

for( int i = thread; i<C*4*B; i += B){
shared_A[i] = AStart[i];
//if(block==32) printf("%f \n", shared_A[i+240*threadIdx.x]);
}



__syncthreads();

/*
if(block==32 && thread == 1) {
for( int i = 0; i<240; i++){
printf("%f %f\n", shared_A[i + 240*31], *(A+i+31*240+(BLOCK_SIZE)*(blockIdx.x)));
}
}*/



float current[] = { 1.0, 0.0, 0.0, 1.0} ;
float temp[4];

for(int i = 0; i<C*4; i += 4){

float mat00 = shared_A[i + C*4*threadIdx.x];
float mat01 = shared_A[i+1 + C*4*threadIdx.x];
float mat10 = shared_A[i+2 + C*4*threadIdx.x];
float mat11 = shared_A[i+3 + C*4*threadIdx.x];

//if(threadIdx.x == 2) printf("next matrix %f %f %f %f \n", mat00, mat01, mat10, mat11);
//if(threadIdx.x == 2) printf("should be   %f %f %f %f \n", *(A+i+threadIdx.x*240), *(A+i+1+threadIdx.x*240),*(A+i+2+threadIdx.x*240),*(A+i+3+threadIdx.x*240));


//if(threadIdx.x == 2) printf("this one \n %f %f \n %f %f \n", current[0], current[1], current[2], current[3]);
//if(threadIdx.x == 2) printf("times this  \n %f %f \n %f %f \n", mat00, mat01, mat10, mat11);

temp[0] = current[0] * mat00 + current[1]*mat10;
temp[1] = current[0] * mat01 + current[1]*mat11;
temp[2] = current[2] * mat00 + current[3]*mat10;
temp[3] = current[2] * mat01 + current[3]*mat11;

current[0] = temp[0];
current[1] = temp[1];
current[2] = temp[2];
current[3] = temp[3];


//if(threadIdx.x == 2) printf("equals \n %f %f \n %f %f \n", current[0], current[1], current[2], current[3]);


}

//if(block==32)printf("writing shared results \n %d %d \n %d %d \n", current[0], current[1], current[2], current[3]);

__shared__ float shared_results[B*4];

shared_results[threadIdx.x*4] = current[0];
shared_results[threadIdx.x*4+1] = current[1];
shared_results[threadIdx.x*4+2] = current[2];
shared_results[threadIdx.x*4+3] = current[3];

__syncthreads();
if(threadIdx.x == 0){

float current[] = { 1.0, 0.0, 0.0, 1.0} ;

	for(int i = 0; i<B; i += 4){

	temp[0] = current[0] * shared_results[threadIdx.x*4] + current[1] * shared_results[threadIdx.x*4 + 2];
	temp[1] = current[0] * shared_results[threadIdx.x*4+1] + current[1] * shared_results[threadIdx.x*4 + 3];
	temp[2] = current[2] * shared_results[threadIdx.x*4] + current[3] * shared_results[threadIdx.x*4 + 2];
	temp[3] = current[2] * shared_results[threadIdx.x*4+1] + current[3] * shared_results[threadIdx.x*4 + 3];
	
	current[0] = temp[0];
	current[1] = temp[1];
	current[2] = temp[2];
	current[3] = temp[3];
	

	//printf(" shared results \n %d %d \n %d %d \n", shared_results[threadIdx.x*4], shared_results[threadIdx.x*4+1], shared_results[threadIdx.x*4+2], shared_results[threadIdx.x*4+3]);

	}

//if(block==32)printf("block partial \n %f %f \n %f %f\n", current[0], current[1], current[2], current[3]);

float* partial_mult_start = partial_mult + 4 * block;
partial_mult_start[0] = current[0];
partial_mult_start[1] = current[1];
partial_mult_start[2] = current[2];
partial_mult_start[3] = current[3];



}



}
