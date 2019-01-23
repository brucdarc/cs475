import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import copy as cp
cores = [1,2,3,4,5,6,7,8]
iterations = 7

def workData(fileName):
	with open(fileName, 'r') as data:
		threadNum = []	
		for x in range(0, len(cores)):
			print(x)
			
			threadData = []
			for y in range(0,iterations):
				time = parse_output_sieve(data)
				threadData.append(float(time))
			print(threadData)
			threadNum.append(threadData) 
		averages = computeAverages(threadNum)
		plotStatsCores(averages)	
	return


#compute the averages for each of the 7 iterations of each core count and return it
def computeAverages(threadNum):
	averages = []
	for x in range(0,len(threadNum)):
		sum = 0
		for y in range(0,len(threadNum[x])):
			sum += threadNum[x][y]
		averages.append(sum/len(threadNum[x]))
	#print(averages)
	return averages














#plot
def plotStatsCores(averages):

#compute and graph speed vs cores
	plt.subplot(231)
	plt.plot(cores,averages)
	plt.plot(cores, [averages[0]/core for core in cores])
	plt.xlabel("Cores")
	plt.xticks([2,4,6,8])
	plt.ylabel(" Average Execution time")
	blue_line = mpatches.Patch(color="blue", label="Actual")
	orange_line = mpatches.Patch(color="orange", label="Ideal")
	plt.legend(handles=[orange_line, blue_line])


#compute and graph speedup vs cores
	plt.subplot(232)
	plt.xlabel("Cores")
	plt.xticks([2,4,6,8])
	plt.ylabel("Speedup")
	speedups = computeSpeedup(averages)
	plt.plot(cores,speedups)
	plt.plot(cores, cores)
	blue_line = mpatches.Patch(color="blue", label="Actual")
	orange_line = mpatches.Patch(color="orange", label="Ideal")
	plt.legend(handles=[orange_line, blue_line])


#compute and graph effeciencies vs cores
	plt.subplot(233)
	plt.xlabel("Cores")
	plt.xticks([2,4,6,8])
	plt.ylabel("Effeciency")
	plt.ylim(0,1.1)
	plt.yticks([0,.25,.5,.75,1])
	effeciencies = computeEffeciency(speedups)
	plt.plot(cores,effeciencies)
	plt.plot(cores,[1,1,1,1,1,1,1,1])
	blue_line = mpatches.Patch(color="blue", label="Actual")
	orange_line = mpatches.Patch(color="orange", label="Ideal")
	plt.legend(handles=[orange_line, blue_line])

#plot table of average time for each core count
	plt.subplot(234)
	plt.axis('tight')
	plt.axis('off')
#cellText needs to be a matrix/double array to work properly
	plt.table(cellText=[[str(x)] for x in averages], rowLabels = [str(core) for core in cores], loc= 'center')

#plot table of speedup for each core count
	plt.subplot(235)
	plt.axis('tight')
	plt.axis('off')
	plt.table(cellText=[[str(x)] for x in speedups], rowLabels = [str(core) for core in cores], loc= 'center')

#plot table of effeciency for each core count
	plt.subplot(236)
	plt.axis('tight')
	plt.axis('off')
	plt.table(cellText=[[str(x)] for x in effeciencies], rowLabels = [str(core) for core in cores], loc= 'center')
#display graphs
	plt.savefig('parallel-results-plot.png')
	plt.show()
	return






















#compute speedup value for each number of cores: sequential time/parallel time
def computeSpeedup(averages):
	sequential_time = averages[0]
	result = [sequential_time/time for time in averages]
	return result

#compute effeciency: speedup/cores
def computeEffeciency(speedups):
	result = []
	for x in range(0,len(cores)): result.append(speedups[x]/cores[x])
	return result
	

#parses the output for the mergesort code
def parse_output_merge_sort(outStr):
	time = outStr[14:22]
	return time

def parse_output_sieve(data):
	data.readline()
	data.readline()
	words = data.readline().split()
	result = cp.copy(words[3])
	print(result)
	data.readline()
	return result[:len(result)-1]

if __name__ == "__main__":
	if len(sys.argv) is 1: 
		print("provide filename")
		
	if len(sys.argv) is 2:
		workData(sys.argv[1])
		

