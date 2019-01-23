///
/// MM2chain.cu
/// By Waruna Ranasinghe 
/// Created: 18 Aug 2017
/// Last Modified: 

///NOTE: Please read all the comments before modifying the file. Failure to maintain
//the required variable names and function names will be penalized. 

//Computes the matrix multiplication of sequence of 2x2 matrices.
//The operation is associative but not commutative. Therefore you cannot
//change the order of matrix multiplications

//Includes
#include <stdio.h>
#include "MM2chainKernel.h"
#include "timer.h"

//defines

/**
 * This macro checks return value of the CUDA runtime call and exits
 * the application if the call failed.
 */
#define CUDA_CHECK_RETURN(value) {                      \
  cudaError_t _m_cudaStat = value;                    \
  if (_m_cudaStat != cudaSuccess) {                   \
    fprintf(stderr, "Error: %s at line %d in file %s\n",          \
        cudaGetErrorString(_m_cudaStat), __LINE__, __FILE__);   \
    exit(1);                              \
  } }

#define epsilon (float)1e-5

///
/// main
///
int main(int argc, char** argv) {
	int G; //number of thread blocks in the grid	
	int n; //number of 2x2 matrices

	//host variables
	float result[4]; // your final answer should be assigned to this variable
	float result_temp[4];
	float *h_A; //input 2x2 matrix sequence. Stored in a 1D array
	float *h_matmults; //partial output matmults per thread block
	//device variables
	float *d_A; //input 2x2 matrix sequence. Stored in a 1D array
	float *d_matmults; //partial output matmults per thread block
	
	if (argc < 2) {
		printf("Usage: %s G\n\tG - number of thread blocks in the grid\n", argv[0]);
		exit(0);
	} 

	//init size params
	G = atoi(argv[1]);
	n=B*G*C;

	printf("Number of threads blocks: %d\nNumber of threads per block: %d\nNumber of matrices per thread: %d\n", G, B, C);
	//allocating memory for host variables
	h_A = (float *)malloc(n*4*sizeof(float));
	if (h_A==NULL) {
		fprintf(stderr, "Failed to allocate host array h_A!\n"); 
		exit(-1);
	}

	h_matmults = (float *)malloc(G*4*sizeof(float));
	if (h_matmults==NULL) {
		fprintf(stderr, "Failed to allocate host array h_matmults!\n");
		exit(-1);
	}

	//initializing input matrices
	//  We repeat the following sequence of matrices      
	//  |1.0 0.0| |4.0 3.0| |1.0  0.0| |0.4 -0.3|
	//  |0.5 1.0| |0.0 2.5| |-0.5 1.0| |0.0 0.25|
	//         
	for (int i=0; i<n*4; i+=16) {
		h_A[i]=1.0f;
		h_A[i+1]=0.0f;
		h_A[i+2]=0.5f;
		h_A[i+3]=1.0f;
		h_A[i+4]=4.0f;
		h_A[i+5]=3.0f;
		h_A[i+6]=0.0f;
		h_A[i+7]=2.5f;
		h_A[i+8]=1.0f;
		h_A[i+9]=0.0f;
		h_A[i+10]=-0.5f;
		h_A[i+11]=1.0f;
		h_A[i+12]=0.4f;
		h_A[i+13]=-0.3f;
		h_A[i+14]=0.0f;
		h_A[i+15]=0.25f;
	}	

	CUDA_CHECK_RETURN(cudaSetDevice(0));


	//Allocating the device memory for input vector. 
	CUDA_CHECK_RETURN(cudaMalloc((void **)&d_A, n*4*sizeof(float)));	

	//allocate device memory for the partial output
	CUDA_CHECK_RETURN(cudaMalloc((void **)&d_matmults, G*4*sizeof(float)));	

	initialize_timer ();
	start_timer();
	//copy the host input matrices array h_A to the device input array d_A in device
	//memory	
	CUDA_CHECK_RETURN(cudaMemcpy(d_A, h_A, n*4*sizeof(float), cudaMemcpyHostToDevice));

	float time_input, time_gpu, time_out; 
  /* Start Timer */
	//initialize_timer ();
	//start_timer();

	stop_timer();
	time_input=elapsed_time ();
	reset_timer();
	start_timer();
	//Launch the reduce CUDA kernel with G blocks per grid and B threads per
	//block
	multiply<<<G, B>>>(d_A, d_matmults);

	//check whether there were errors while launching the CUDA kernel
	CUDA_CHECK_RETURN(cudaGetLastError());

	//wait for the kernel to finish
	CUDA_CHECK_RETURN(cudaThreadSynchronize());

	/* stop timer */
	stop_timer();
	time_gpu=elapsed_time ();
	reset_timer();
	start_timer();

	//Copy partial results back to host
	CUDA_CHECK_RETURN(cudaMemcpy(h_matmults, d_matmults, G*4*sizeof(float), cudaMemcpyDeviceToHost));

	result[0] = 1.0f;
	result[1] = 0.0f;
	result[2] = 0.0f;
	result[3] = 1.0f;
	//compute final answer by multiplying the partial answers of threads from
	//GPU
	for (int i=0; i<G; i++) {
		result_temp[0] = result[0]*h_matmults[i*4] + result[1]*h_matmults[i*4+2];
		result_temp[1] = result[0]*h_matmults[i*4+1] + result[1]*h_matmults[i*4+3];
		result_temp[2] = result[2]*h_matmults[i*4] + result[3]*h_matmults[i*4+2];
		result_temp[3] = result[2]*h_matmults[i*4+1] + result[3]*h_matmults[i*4+3];
		result[0] = result_temp[0];
		result[1] = result_temp[1];
		result[2] = result_temp[2];
		result[3] = result_temp[3];
	}

	stop_timer();
	time_out=elapsed_time ();
	printf("Output:\n%f %f\n%f %f\nTime to copy input data: %f s\nTime to compute[GPU]: %f s\nTime to compute output: %f s\n", result[0], result[1], result[2], result[3], time_input, time_gpu, time_out);
//	printf("Result: %f , Elapsed time [GPU]: %f , all: %f\n", result, time);

//	if (result[0]-1.0f < epsilon && result[1]-0.0f < 0.2f && result[2]-0.0f < epsilon && result[3]-1.0f < epsilon) {
	if (fabsf(result[0]-1.0f) < epsilon && fabsf(result[1]-0.0f) < 0.2f && fabsf(result[2]-0.0f) < epsilon && fabsf(result[3]-1.0f) < epsilon) {
		printf("Test passed.\n");
	} else {
		printf("Test failed.\n");
	}


	//cleaning up
	free(h_A);
	free(h_matmults);

	return 0;
}

