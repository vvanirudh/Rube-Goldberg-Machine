#! /usr/bin/env python3.2
import re

def modify(s):
     lines=s.split("\n")
     acc=""
     for w in lines:
             str1=str(w)
             if str1!="" and str1[0]!="\\" and str1[0]!="%":
                     acc = acc + str1
     return acc

f=open("doc/g10_prof_report.tex","r")
f2=open("doc/g10_lab09_report.html","w")

complete=f.read()
#maketitle=re.split(r'\maketitle',complete)
#titlehelper=re.split(r'\title',maketitle)

maketitle=complete.split("\maketitle")
titlehelper=maketitle[0].split("\\title")
titlehelper2=titlehelper[1].split("\n")
title=str(titlehelper2[0])
#print(title)
head="""<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
<link rel="stylesheet" type="text/css" href="index.css" />
<title>""" + title[2:-1] + """</title>
</head>"""
#print(head)

data=maketitle[1]
sections=data.split("\section")
body="<body>"
#remember we need to add </body> at the end
for i in (range(len(sections))):
	if i!=0:
		h1helper= sections[i].split("\n")
		h1helper2= str(h1helper[0]) 
		h1="<h1>" + h1helper2[1:-1].replace("{","").replace("*","") + "</h1>"
		subsections=sections[i].split("\subsection")
		#subsections[0] just contains text for the section
		#need to remove images,\\
		h1bodyhelper = str(subsections[0])
		h1body="<p>" + modify(h1bodyhelper[((len(h1))-7):]) + "</p>"
		body = body + "\n" + h1 + "\n" + h1body + "\n"
		for j in (range(len(subsections))):
			if i==2 and j==0:
				body= body + """<img src="orig-machine.png" alt="Original Machine" width=80% height="350" />"""
			elif i==3 and j==0:
				body= body + """<img src="actual-machine.png" alt="Actual Machine" width=80% height="350" />"""
			if j!=0:
				h2helper= subsections[j].split("\n")
				h2helper2= str(h2helper[0]) 
				#braces might creep in over here
				h2="<h2>" + h2helper2[1:-1].replace("{","").replace("*","") + "</h2>"
				subsubsections=subsections[j].split("\subsubsection")
				#subsubsections[0] just contains text for the subsection
				#need to remove images,\\
				h2bodyhelper = str(subsubsections[0])
				h2body="<p>" + modify(h2bodyhelper[((len(h2))-7):]) + "</p>"
				#h2body="<p>" + str(subsubsections[0]) + "</p>"
				body = body + "\n" + h2 + "\n" + h2body + "\n"
				if i==8 and j==1:
					body= body + """<img src="non-optimized.png" alt="Without Optimizations" width=80% height="200" />"""
				elif i==8 and j==2:
					body= body + """<img src="optimized.png" alt="Without Optimizations" width=80% height="80" />"""
				elif i==4 and j==1:
					body= body + """<img src="../plots_doc/g10_plot01_re.png" alt="Without Optimizations" width=80% height="350" />"""
				elif i==4 and j==2:
					body= body + """<img src="../plots_doc/g10_plot02_re.png" alt="Without Optimizations" width=80% height="350" />"""
				elif i==4 and j==3:
					body= body + """<img src="../plots_doc/g10_plot03_1_re.png" alt="Without Optimizations" width=80% height="350" />"""
					body= body + """<img src="../plots_doc/g10_plot03_2_re.png" alt="Without Optimizations" width=80% height="350" />"""	
				elif i==4 and j==4:
					body= body + """<img src="../plots_doc/g10_plot04_re.png" alt="Without Optimizations" width=80% height="350" />"""
				elif i==4 and j==5:
					body= body + """<img src="../plots_doc/g10_plot05_re.png" alt="Without Optimizations" width=80% height="350" />"""
				for k in (range(len(subsubsections))):
					if k!=0:
						h3helper= subsubsections[k].split("\n")
						h3helper2= str(h3helper[0]) 
						#braces might creep in over here
						h3="<h3>" + h3helper2[1:-1].replace("{","").replace("*","") + "</h3>"
						h3bodyhelper= (subsubsections[k].split("}"))
						#need to remove images,\\
						h3body="<p>" + str(h3bodyhelper[1]) + "</p>" 
						body = body + "\n" + h3 + "\n" + modify(h3body) + "\n"
body=body + "</body>"
final = head + body + "\n</html>"
#print(final)
f2.write(final)
f.close()
f2.close()

