#!/bin/bash
rm data
make clean
make
export OMP_NUM_THREADS=1
for i in `seq 1 6`; do
	export OMP_NUM_THREADS=$i;
	echo $i;
	for j in `seq 1 5`; do
			./jacOMP 120000 12000 >> data; 

done;
done
python3 graph.py data
  
        
