#!/bin/bash
for i in `seq 1 8`; do
	export OMP_NUM_THREADS=$i;
	echo $i;
	for j in `seq 1 7`; do
			./stencil_2D 800 2000 >> data; 

done;
done

  
        
