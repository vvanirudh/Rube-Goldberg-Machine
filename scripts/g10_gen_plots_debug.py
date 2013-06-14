import matplotlib.pyplot as plt
import re
import numpy as np

#f=open("data/data.csv","r")
#data=f.read()

data=np.loadtxt("data/g10_data.csv",delimiter=",")

#print(data)

step=[]
vel=[]
coll=[]
pos=[]
loop=[]

rstep=[]
rvel=[]
rcoll=[]
rpos=[]
rloop=[]

maxstep=[]
minstep=[]

step1=[]
step2=[]
stepvalue=0

k=[]
for j in range(100):
	step.append(0)
	vel.append(0)
	coll.append(0)
	pos.append(0)
	loop.append(0)
	
	rstep.append(0)
	rvel.append(0)
	rcoll.append(0)
	rpos.append(0)
	rloop.append(0)
	
	maxstep.append(0)
	minstep.append(1000)
	
	step1.append(0)
	
	k.append(j+1)

for i in data:
	step[int(i[1])-1]=step[int(i[1])-1]+float(i[2])
	coll[int(i[1])-1]=coll[int(i[1])-1]+float(i[3])
	vel[int(i[1])-1]=vel[int(i[1])-1]+float(i[4])
	pos[int(i[1])-1]=pos[int(i[1])-1]+float(i[5])
	loop[int(i[1])-1]=loop[int(i[1])-1]+float(i[6])
	
	rstep[int(i[0])-1]=rstep[int(i[0])-1]+float(i[2])
	rcoll[int(i[0])-1]=rcoll[int(i[0])-1]+float(i[3])
	rvel[int(i[0])-1]=rvel[int(i[0])-1]+float(i[4])
	rpos[int(i[0])-1]=rpos[int(i[0])-1]+float(i[5])
	rloop[int(i[0])-1]=rloop[int(i[0])-1]+float(i[6])
	
	if maxstep[int(i[1])-1] < float(i[2]):
		maxstep[int(i[1])-1]=float(i[2])
	if minstep[int(i[1])-1] > float(i[2]):
		minstep[int(i[1])-1]=float(i[2])
	if int(i[1])==1:
		step1[int(i[0])-1]=float(i[2])
		#stepvalue=stepvalue+float(i[2])
		#step2.append(stepvalue)

xestep=[x/100.0 for x in step]
xeloop=[x/100.0 for x in loop]
xevel=[x/100.0 for x in vel]
xecoll=[x/100.0 for x in coll]
xepos=[x/100.0 for x in pos]

rxestep=[x/100.0 for x in rstep]
rxeloop=[x/100.0 for x in rloop]
rxevel=[x/100.0 for x in rvel]
rxecoll=[x/100.0 for x in rcoll]
rxepos=[x/100.0 for x in rpos]

error1=[]
error2=[]
for i in range(100):
	error1.append(maxstep[i]-xestep[i])
	error2.append(xestep[i]-minstep[i])
###############################################################################################
plt.figure(1)
plt.plot(k,xestep,'bx',label="Average Step time")
plt.plot(k,xeloop,'rx',label="Average Loop time")
plt.xlabel("Iteration value")
plt.ylabel("time")
plt.title("Average step time and loop time vs. iteration value")
plt.legend()

plt.savefig("plots_non1/g10_plot01.png")
####################################################################################################
plt.figure(2)
plt.plot(k,xestep,'bx',label="Average step time")
plt.plot(k,xevel,'rx',label="Average velocity time")
plt.plot(k,xecoll,'gx',label="Average collision time")
plt.plot(k,xepos,'cx',label="Average position time")

plt.xlabel("Iteration value")
plt.ylabel("time")
plt.title("Average step, velocity, collision and position time vs. iteration value")
plt.legend()
plt.savefig("plots_non1/g10_plot02.png")	
#################################################################################################
plt.figure(3)
plt.plot(k,rxestep,'bx',label="Average step time")
plt.plot(k,rxeloop,'rx',label="Average loop time")
plt.xlabel("Rerun value")
plt.ylabel("time")
plt.title("Average step and loop time vs. rerun value")
plt.legend()
plt.savefig("plots_non1/g10_plot03_1.png")
####################################################################################################
plt.figure(4)
plt.plot(k,rxestep,'bx',label="Average step time")
plt.plot(k,rxevel,'rx',label="Average velocity time")
plt.plot(k,rxecoll,'gx',label="Average collision time")
plt.plot(k,rxepos,'cx',label="Average position time")

plt.xlabel("Rerun value")
plt.ylabel("time")
plt.title("Average step, velocity, collision and position time vs. rerun value")
plt.legend()
plt.savefig("plots_non1/g10_plot03_2.png")
#####################################################################################################
plt.figure(5)
plt.plot(k,xestep,'b-',label="Average step time")
plt.errorbar(k,xestep,yerr=[error2,error1],ecolor='green',label="Deviation in step time over reruns")
plt.legend()
plt.title("average step time vs. iteration value with error bars")
plt.xlabel("iteration value")
plt.ylabel("time")
plt.savefig("plots_non1/g10_plot04.png")
########################################################################################################
plt.figure(6)

values, b=np.histogram(step1)

sum=0
a=[0]
c=[]
for i in values:
	sum+=i
	a.append(sum)
c.append(b[0])
for i in range(len(b)-1):
	c.append((b[i]+b[i+1])/2.0)

plt.plot(c,a,label="Cumulative frequency")
#plt.hist(step1,bins=20,color='0.8',cumulative=True,label="Cumulative frequency")
plt.hist(step1,bins=b,color='g',label="Frequency")
plt.legend()
plt.xlabel("step time")
plt.ylabel("frequency")
plt.title("Frequency of average step time for iteration value of 1")
plt.savefig("plots_non1/g10_plot05.png")

#print(step1)
