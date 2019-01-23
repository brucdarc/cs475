import subprocess
import numpy as np
import matplotlib.pyplot as plt
import os
etimes = []
iterations = 4


#averages = [4.940230000000001, 2.47859575, 1.681896, 1.2652204999999999, 1.0504464999999998, 0.89968825]
#ompav = [1.6122232, 0.8859155999999999, 0.6194838, 0.48160179999999997, 0.3821332, 0.33444080000000004]


buffsizes = [5,10,20,40,50,100,125,150,200,250,500,1000,2000,4000,8000]

etimes = [1.01134, 0.957347, 0.963431, 1.012684, 0.760454, 0.816748, 0.75861, 0.771664, 0.649152, 0.697098, 0.657506, 0.663722, 0.673084, 0.602738, 0.601329, 0.60652, 0.802792, 0.595246, 0.613106, 0.610235, 0.59788, 0.626597, 0.597436, 0.600571, 0.575222, 0.593494, 0.5993, 0.608139, 0.688806, 0.595649, 0.577119, 0.59706, 0.600632, 0.59884, 0.607626, 0.554752, 0.620786, 0.595606, 0.619942, 0.604936, 0.591507, 0.5814, 0.647262, 0.608342, 0.619045, 0.626488, 0.619389, 0.590326, 0.62486, 0.645972, 0.606645, 0.617403, 0.665856, 0.725557, 0.685869, 0.891096, 0.825247, 0.77701, 0.794302, 0.797698]

averages = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,]

"""
for nump in buffsizes:


	for iteration in range(0,iterations):

		print(nump)
		#test = subprocess.Popen(["mpirun", "-np", "6", "--hostfile", "h2", "--mca", "bt1_tcp_if_include", "eno1", "jacMPI", "120000", "12000", str(nump)], stdout=subprocess.PIPE)
	
		output = subprocess.check_output("mpirun -np 12 --hostfile h2 --mca btl_tcp_if_include eno1 jacMPI 480000 12000 " + str(nump), shell=True)

		print(output)

		time = output[-13:-5]




		print(time)
		print(float(time))
		etimes.append(float(time))

"""




print(etimes)


for nump in range(0,len(buffsizes)):
	for iteration in range(0,iterations):
		averages[nump] += etimes.pop(0)
	averages[nump] = averages[nump]/iterations

print(averages)
cores = [1,2,3,4,5,6]

plt.plot(buffsizes, averages)
#plt.plot(buffsizes, ompav, "X")
plt.ylabel("Exec Time")
plt.xlabel("Number of processors")
plt.show()



