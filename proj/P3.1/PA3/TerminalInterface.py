import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import subprocess
import graph

def getFunctionCall():
	return "./sieve1 "

def getVarriedArguments():
	return ["100000", "200000", "300000"]



def plotVaryingInput(command, args):
	averages = []
	output = []
	current_args = []
	averages0 = []
	output0 = []
	current_args0 = []
	for arg in args:
		for x in range(0,4):

			#I am the spaghetti master there is no greater spaghetti master than me			
			#
			data0 = subprocess.check_output(" ./sieve " + arg, shell=True)
			words0 = data0.split()
			output0.append(float(parse_output_sieve_string(words0).decode("ascii")))
			current_args0.append(float(parse_output_sieve_string(words0).decode("ascii")))
			

			#spaghettios spaghettiNOs


			data = subprocess.check_output(command + arg, shell=True)
			words = data.split()
			output.append(float(parse_output_sieve_string(words).decode("ascii")))
			current_args.append(float(parse_output_sieve_string(words).decode("ascii")))
			print(x);



		averages.append(sum(current_args)/float(len(current_args)))
		current_args = []
		averages0.append(sum(current_args0)/float(len(current_args0)))
		current_args0 = []
	plt.subplot(211)
	plt.title("Sieve v. Sieve1")
	#plt.xscale("log");
	plt.yscale("log");
	plt.xlabel("Iterations")
	plt.xticks([100000, 200000, 300000])
	#plt.xticks([500000000, 1000000000, 1500000000])
	plt.ylabel("Time")
	iterations = [arg.split()[0] for arg in args]
	plt.plot(iterations,averages)
	plt.plot(iterations,averages0)
	blue_line = mpatches.Patch(color="blue", label="Sieve1")
	orange_line = mpatches.Patch(color="orange", label="Sieve")
	plt.legend(handles=[orange_line, blue_line])

	plt.subplot(212)
	plt.axis('tight')
	plt.axis('off')
	print(averages)
	print(averages0)
	plt.table(cellText=[[str(averages0[x]),str(averages[x])] for x in range(0,len(averages))],  loc= 'center', colLabels = ["sieve1","sieve3"], )

	print(averages)
	print(output)



	plt.show()
	

def parse_output_sieve_string(output):
	return output[-2]



if __name__ == "__main__":
	plotVaryingInput(getFunctionCall(),getVarriedArguments())
