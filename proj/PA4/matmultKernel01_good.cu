///
/// matmultKernel00.cu
/// For CSU CS575 Spring 2011
/// Instructor: Wim Bohm
/// Based on code from the CUDA Programming Guide
/// Modified by Wim Bohm and David Newman
/// Created: 2011-01-27
/// Last Modified: 2011-02-23 DVN
///
/// Multiplies two matrices using CUDA: A x B = C
///
/// Copy this file and modify the MatMultKernel device function for
/// each of your experiments. 
///

#include "matmultKernel.h"

// Define a gpu kernel to perform matrix multiplication
// of A x B = C.
__global__ void MatMulKernel(Matrix A, Matrix B, Matrix C){

  // matrix blocks
  float *Asub, *Bsub, *Csub;
  // Putting these into registers speeds access.
  int thread_row = threadIdx.y;
  int thread_col = threadIdx.x;

//this is where the thread blocks start in the thread space
  int block_row = blockIdx.y;
  int block_col = blockIdx.x;

//this is where they go into memory
  int footprint_row = block_row*2;
  int footprint_col = block_col*2;

//4 different C values
  float Cvalue0 = 0;
  float Cvalue1 = 0;
  float Cvalue2 = 0;
  float Cvalue3 = 0;



  Csub = &C.elements[C.stride * footprint_row * FOOTPRINT_SIZE + FOOTPRINT_SIZE * footprint_col];

  for (int m = 0;  m < (A.width / FOOTPRINT_SIZE); ++m){


  Asub = &A.elements[A.stride * FOOTPRINT_SIZE * footprint_row + FOOTPRINT_SIZE * m];
  Bsub = &B.elements[B.stride * FOOTPRINT_SIZE * m + FOOTPRINT_SIZE * footprint_col];




  
  __shared__ float shared_A[FOOTPRINT_SIZE][FOOTPRINT_SIZE];
  __shared__ float shared_B[FOOTPRINT_SIZE][FOOTPRINT_SIZE];



  shared_A[thread_row][thread_col] = Asub[A.stride * thread_row + thread_col];
  shared_B[thread_row][thread_col] = Bsub[B.stride * thread_row + thread_col]; 
  
  shared_A[thread_row][thread_col+BLOCK_SIZE] = Asub[A.stride * thread_row + thread_col+BLOCK_SIZE];
  shared_B[thread_row][thread_col+BLOCK_SIZE] = Bsub[B.stride * thread_row + thread_col+BLOCK_SIZE]; 

  shared_A[thread_row+BLOCK_SIZE][thread_col] = Asub[A.stride * (thread_row + BLOCK_SIZE) + thread_col];
  shared_B[thread_row+BLOCK_SIZE][thread_col] = Bsub[B.stride * (thread_row + BLOCK_SIZE) + thread_col]; 
  
  shared_A[thread_row+BLOCK_SIZE][thread_col+BLOCK_SIZE] = Asub[A.stride * (thread_row + BLOCK_SIZE) + thread_col+BLOCK_SIZE];
  shared_B[thread_row+BLOCK_SIZE][thread_col+BLOCK_SIZE] = Bsub[B.stride * (thread_row + BLOCK_SIZE) + thread_col+BLOCK_SIZE]; 
   //make sure all threads 
   __syncthreads();



#pragma unroll
    for( int e = 0; e<FOOTPRINT_SIZE; e++){
//top left and top right
	Cvalue0 += shared_A[thread_row][e]*shared_B[e][e];
	Cvalue1 += shared_A[thread_row][e]*shared_B[e][thread_col+BLOCK_SIZE];
	Cvalue2 += shared_A[thread_row+BLOCK_SIZE][e]*shared_B[e][thread_col];
	Cvalue3 += shared_A[thread_row+BLOCK_SIZE][e]*shared_B[e][thread_col+BLOCK_SIZE];

    }

    // Synchronize to ensure all Cvalues have been incremented
    // before reading in the next shared_A AND shared_B BLOCKS
    __syncthreads();




  }
  // Write Csub to GLOBAL memory.
  // Each thread writes its own cell value.
 
  Csub[thread_row * C.stride + thread_col  ] = Cvalue0;
  Csub[thread_row * C.stride + thread_col  + BLOCK_SIZE] = Cvalue1;
  Csub[thread_row * C.stride + thread_col  + BLOCK_SIZE*C.stride] = Cvalue2;
  Csub[thread_row * C.stride + thread_col  + BLOCK_SIZE*C.stride + BLOCK_SIZE] = Cvalue3;

}

