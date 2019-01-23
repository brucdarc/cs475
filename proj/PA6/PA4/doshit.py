import subprocess
import numpy as np
import matplotlib.pyplot as plt

etimes = []
iterations = 4


#averages = [4.940230000000001, 2.47859575, 1.681896, 1.2652204999999999, 1.0504464999999998, 0.89968825]
ompav = [1.6122232, 0.8859155999999999, 0.6194838, 0.48160179999999997, 0.3821332, 0.33444080000000004]
averages = [0,0,0,0,0,0]

for nump in range(1,7):


	for iteration in range(0,iterations):

		print(nump)
		test = subprocess.Popen(["mpirun", "-np", str(nump) , "jacMPI", "120000", "12000", "1"], stdout=subprocess.PIPE)
		output = test.communicate()[0]
		print(output)

		time = output[105:113]




		print(time)
		print(float(time))
		etimes.append(float(time))






print(etimes)


for nump in range(1,7):
	for iteration in range(0,iterations):
		averages[nump-1] += etimes.pop(0)
	averages[nump-1] = averages[nump-1]/iterations

print(averages)
cores = [1,2,3,4,5,6]

plt.plot(cores, averages)
plt.plot(cores, ompav, "X")
plt.ylabel("Exec Time")
plt.xlabel("Number of processors")
plt.show()



