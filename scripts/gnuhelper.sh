#!/bin/bash
awk -F, 'BEGIN{
	for(i=1;i<=100;i++)
	{
		maximum[i]=0;
		minimum[i]=100;
		average[i]=0;
	}
}
{
	average[$2]=average[$2]+$3;
	if(maximum[$2]<$3)
	{
		maximum[$2]=$3;
	}
	if(minimum[$2]>$3)
	{
		minimum[$2]=$3;
	}
}
END{
	for (i=1; i<=100; i++) {
		printf "%d,%f,%f\n",i,maximum[i]-minimum[i],average[i]/100
	}
}' ./data/lab05_g10_data.csv > ./data/lab5_tmp.csv
