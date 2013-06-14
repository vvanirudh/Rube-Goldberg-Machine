#!/bin/bash
FILEDIR=./data

cd $FILEDIR

awk '{if(NR%6==1) {f=substr(FILENAME,index(FILENAME,"-")+1);g=substr(f,index(f,"-")+1);h=substr(g,1,index(g,".")-1); printf "%d,%d,",h,$NF} else if(NR%6==0) {printf "%f\n", $(NF-1)} else {printf "%f,", $(NF-1)} }' *.txt > lab.csv


sort -g --field-separator=',' --key=1 -g --field-separator=',' --key=2 lab.csv > lab05_g10_data.csv
rm lab.csv

