#!/bin/bash
make clean
make
for i in `seq 1 8`; do
	export OMP_NUM_THREADS=$i;
	echo $i;
	for j in `seq 1 7`; do
			./Merge_sort_par 10000000 >> data; 

done;
done
python graph.py data
  
        
