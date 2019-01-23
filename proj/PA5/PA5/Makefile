### CS475 Assignment
### By Waruna Ranasinghe 
### Created: 16 Aug 2017
### Last Modified: 
###
###

CC:=nvcc
LIB:=
INCLUDES:=
CUDA_OPTIONS:= -O3 --ptxas-options -v --gpu-architecture=sm_61 --compiler-bindir  /usr/local/gcc-6.4.0/bin -std=c++11 -I/s/bach/g/under/cutreap/cuda-patches/include

TAR_FILE_NAME := CUDA1.tar
EXECS := MM2chain00 MM2chain01
all: $(EXECS)


MM2chain01: MM2chain.cu MM2chainKernel.h MM2chainKernel01.o timer.o
	$(CC) $< MM2chainKernel01.o timer.o -o $@ $(LIB) $(INCLUDES) $(CUDA_OPTIONS)

MM2chain00: MM2chain.cu MM2chainKernel.h MM2chainKernel00.o timer.o
	$(CC) $< MM2chainKernel00.o timer.o -o $@ $(LIB) $(INCLUDES) $(CUDA_OPTIONS)


%.o : %.cu MM2chainKernel.h timer.h
	$(CC) $< -c -o $@ $(CUDA_OPTIONS)

clean:
	rm -f $(EXECS) *.o 

tar: MM2chain.cu  MM2chainKernel.h MM2chainKernel01.cu MM2chainKernel00.cu  report.pdf
	tar -cf PA5.tar MM2chain.cu  MM2chainKernel.h MM2chainKernel01.cu MM2chainKernel00.cu  report.pdf

