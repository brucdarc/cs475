#!/bin/bash
rm data
make clean
make
for i in `seq 1 8`; do
	export OMP_NUM_THREADS=$i;
	echo $i;
	for j in `seq 1 7`; do
			./knap3 sample/k50x2M.txt 1 >> data; 

done;
done
python3 graph.py data
  
        
