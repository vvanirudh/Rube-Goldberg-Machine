#!/bin/bash

awk -F, 'BEGIN{
	for(i=1;i<=100;i++)
	{
		values[i]=0;
	}
}
{
	if($2==1)
	{
		values[$1]=$3;
	}
}
END{
	for(i=1;i<=100;i++)
	{
		printf "%d,%f\n" ,i,values[i]
	}
}' ./data/lab05_g10_data.csv > ./data/lab5_tmp2.csv
