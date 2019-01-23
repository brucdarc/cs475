CC = gcc
CFLAGS = -O3 -g  
LDLIBS = -lm -g 

SEQFLAGS = -Wall -Wshadow -O3 -g -march=native
objs = genann.o

CUDA_OPTIONS:= -O3 --ptxas-options -v --gpu-architecture=sm_61 --compiler-bindir  /usr/local/gcc-6.4.0/bin -std=c++11 -I/s/bach/g/under/cutreap/cuda-patches/include


all: check example1 example2 example3 example4 

sigmoid: CFLAGS += -Dgenann_act=genann_act_sigmoid_cached
sigmoid: all

threshold: CFLAGS += -Dgenann_act=genann_act_threshold
threshold: all

linear: CFLAGS += -Dgenann_act=genann_act_linear
linear: all



test: test.o genann.o

check: test
	./$^

example1: example1.o genann.o

example2: example2.o genann.o

example3: example3.o genann.o

example4: example4.o genann.o
	nvcc -o example4 genann.o matmultKernel00.o

matmultKernel00.o : matmultKernel00.cu matmultKernel.h 
	nvcc $< -c -o $@ $(CUDA_OPTIONS)



clean:
	$(RM) *.o
	$(RM) test example1 example2 example3 example4 *.exe
	$(RM) persist.txt

.PHONY: sigmoid threshold linear clean
