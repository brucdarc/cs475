#include <stdio.h>
#include "MM2chainKernel.h"




__global__ void multiply(const float* A, float* partial_mult ){

int block = blockIdx.x;
int thread = threadIdx.x;
int BLOCK_SIZE =  gridDim.x;



__shared__ float shared_A[B*C*4];
__shared__ float shared_results[B*4];





const float* AStart = A + ((B)*(blockIdx.x)*C*4);


for( int i = 0; i<C*4; i++){
shared_A[i+thread*C*4] = AStart[i+thread*C*4];

}



__syncthreads();



float current[] = { 1.0, 0.0, 0.0, 1.0} ;
float temp[4];

for(int i = 0; i<C*4; i += 4){

float mat00 = shared_A[i + C*4*threadIdx.x];
float mat01 = shared_A[i+1 + C*4*threadIdx.x];
float mat10 = shared_A[i+2 + C*4*threadIdx.x];
float mat11 = shared_A[i+3 + C*4*threadIdx.x];


temp[0] = current[0] * mat00 + current[1]*mat10;
temp[1] = current[0] * mat01 + current[1]*mat11;
temp[2] = current[2] * mat00 + current[3]*mat10;
temp[3] = current[2] * mat01 + current[3]*mat11;

current[0] = temp[0];
current[1] = temp[1];
current[2] = temp[2];
current[3] = temp[3];


}


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
	


	}


float* partial_mult_start = partial_mult + 4 * block;
partial_mult_start[0] = current[0];
partial_mult_start[1] = current[1];
partial_mult_start[2] = current[2];
partial_mult_start[3] = current[3];



}



}
