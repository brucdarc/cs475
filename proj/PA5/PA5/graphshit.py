#!/usr/bin/python
import sys
import matplotlib as plt
import time
import subprocess
from statistics import mean
MM0 = []
MM1 = []

B = "60"
C = "4"
G = "800000"

for x in range(0,4):
	result0 = subprocess.run(["MM2chain00", G], stdout=subprocess.PIPE)
	result0 = result0.stdout

	#print(str(result))

	result0 = float(result0[202:210])

	print(result0)

	result1 = subprocess.run(["MM2chain01", G], stdout=subprocess.PIPE)
	result1 = result1.stdout

	#print(str(result))

	result1 = float(result1[202:210])

	print(result1)

	MM0.append(result0)
	MM1.append(result1)


print(MM0)
print(MM1)
print(mean(MM0))
print(mean(MM1))


f = open("demofile.txt", "a")
f.write( "B: " + B + " C: "+ C + " G: " + G + " MM2chain00 gpu time: " + str(mean(MM0)) +" MM2chain00 gpu time: " + str(mean(MM1)) + " speedup: " + str(mean(MM0)/mean(MM1)) + "\n")

