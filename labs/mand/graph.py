import sys
import numpy as np
import matplotlib.pyplot as plt
def workData(fileName):
	with open(fileName, 'r') as data:
		threadNum = []	
		for x in range(0, 8):
			print(x)
			
			threadData = []
			for y in range(0,7):
				time = parseOutput(data.readline())
				threadData.append(float(time))
			print(threadData)
			threadNum.append(threadData) 
		averages = computeAverages(threadNum)
		plotshit(averages)	
	return

def computeAverages(threadNum):
	averages = []
	for x in range(0,len(threadNum)):
		sum = 0
		for y in range(0,len(threadNum[x])):
			sum += threadNum[x][y]
		averages.append(sum/len(threadNum[x]))
	print(averages)
	return averages

def plotshit(averages):
	plt.plot([1,2,3,4,5,6,7,8],averages)
	plt.show()



def parseOutput(outStr):
	time = outStr[14:22]
	return time

if __name__ == "__main__":
	if len(sys.argv) is 1: 
		print("provide filename")
		
	if len(sys.argv) is 2:
		workData(sys.argv[1])
		
	
