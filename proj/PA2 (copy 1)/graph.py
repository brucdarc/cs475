import sys
import numpy as np
import matplotlib.pyplot as plt

cores = [1,2,3,4,5,6,7,8]
iterations = 7

def workData(fileName):
	with open(fileName, 'r') as data:
		threadNum = []	
		for x in range(0, len(cores)):
			print(x)
			
			threadData = []
			for y in range(0,iterations):
				time = parse_output_siege(data)
				threadData.append(float(time))
			print(threadData)
			threadNum.append(threadData) 
		averages = computeAverages(threadNum)
		plotStats(averages)	
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
def plotStats(averages):

#compute and graph speed vs cores
	plt.subplot(231)
	plt.plot(cores,averages)
	plt.xlabel("Cores")
	plt.ylabel(" Average Execution time")

#compute and graph speedup vs cores
	plt.subplot(232)
	plt.xlabel("Cores")
	plt.ylabel("Speedup")
	speedups = computeSpeedup(averages)
	plt.plot(cores,speedups)

#compute and graph effeciencies vs cores
	plt.subplot(233)
	plt.xlabel("Cores")
	plt.ylabel("Effeciency")
	effeciencies = computeEffeciency(speedups)
	plt.plot(cores,effeciencies)

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

def parse_output_siege(data):
	data.readline()
	data.readline()
	data.readline()
	words = data.readline().split()
	#print(words)
	return words[-2]

if __name__ == "__main__":
	if len(sys.argv) is 1: 
		print("provide filename")
		
	if len(sys.argv) is 2:
		workData(sys.argv[1])
		
	
