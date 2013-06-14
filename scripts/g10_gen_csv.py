import subprocess

r=open("data/g10_data.csv","w")
r.close()
f=open("data/g10_data.csv","a")

for rerun in range(100):
	for iteration in range(100):
		a=subprocess.check_output(["./bin/cs296_base",str(iteration+1)],universal_newlines=True)
		p=a.split()
		s=str(rerun+1)+","+str(iteration+1)+","+p[8]+","+p[15]+","+p[23]+","+p[31]+","+p[38]+"\n"
		f.write(s)	
f.close()
