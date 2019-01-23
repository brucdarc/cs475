#!/bin/bash
for i in `seq 1 8`; do
	export OMP_NUM_THREADS=$i;
	echo $i;
	for j in `seq 1 7`; do
			./mandOMP 1000 >> data; 

done;
done

  
        
