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




  
  __shared__ float shared_A[FOOTPRINT_SIZE*FOOTPRINT_SIZE];
  __shared__ float shared_B[FOOTPRINT_SIZE*FOOTPRINT_SIZE];

  int offset = 0;

  int Arow = A.stride * thread_row/2;
  int Brow = B.stride * thread_row/2;
  int Acol = thread_col + thread_row%2 * BLOCK_SIZE;
  int Bcol = thread_col + thread_row%2 * BLOCK_SIZE;


  int sharedArow = thread_row/2 * FOOTPRINT_SIZE;
  int sharedBrow = thread_row/2 * FOOTPRINT_SIZE;
  int wFact = BLOCK_SIZE/2 * A.stride;
  int bFact = FOOTPRINT_SIZE * FOOTPRINT_SIZE;

  shared_A[sharedArow + Acol + offset*bFact] = Asub[Arow + Acol + offset*wFact];
  shared_B[sharedBrow + Bcol + offset*bFact] = Bsub[Brow + Bcol + offset*wFact];
  
  offset++;

  shared_A[sharedArow + Acol + offset*bFact] = Asub[Arow + Acol + offset*wFact];
  shared_B[sharedBrow + Bcol + offset*bFact] = Bsub[Brow + Bcol + offset*wFact];
  
  
  offset++;

  shared_A[sharedArow + Acol + offset*bFact] = Asub[Arow + Acol + offset*wFact];
  shared_B[sharedBrow + Bcol + offset*bFact] = Bsub[Brow + Bcol + offset*wFact];  
  
  offset++;

  shared_A[sharedArow + Acol + offset*bFact] = Asub[Arow + Acol + offset*wFact];
  shared_B[sharedBrow + Bcol + offset*bFact] = Bsub[Brow + Bcol + offset*wFact];
  
  
  

   //make sure all threads 
   __syncthreads();



#pragma unroll
    for( int e = 0; e<FOOTPRINT_SIZE; e++){
//top left and top right
	Cvalue0 += shared_A[e*FOOTPRINT_SIZE + thread_col] * shared_B[thread_row + e ];
	Cvalue1 += shared_A[e*FOOTPRINT_SIZE + thread_col + BLOCK_SIZE] * shared_B[thread_row + e + BLOCK_SIZE];
//bot left and bot right
	Cvalue2 += shared_A[e*FOOTPRINT_SIZE + thread_col + BLOCK_SIZE*FOOTPRINT_SIZE] * shared_B[thread_row + e + BLOCK_SIZE*FOOTPRINT_SIZE];
	Cvalue3 += shared_A[e*FOOTPRINT_SIZE + thread_col + BLOCK_SIZE*FOOTPRINT_SIZE + BLOCK_SIZE] * shared_B[thread_row + e + BLOCK_SIZE*FOOTPRINT_SIZE + BLOCK_SIZE];
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

