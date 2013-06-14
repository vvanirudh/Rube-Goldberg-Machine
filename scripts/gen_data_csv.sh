#!/bin/bash
	touch ./data/lab05_g10_data.csv
	rm ./data/lab05_g10_data.csv
	touch ./data/lab05_g10_data.csv
	EXEC_DIR=./bin
	OUTPUT_DIR=../data
	OUTERCOUNT=1
	INNERCOUNT=1
	cd $EXEC_DIR
	while [ $OUTERCOUNT -le 100 ]; do
	INNERCOUNT=1
		while [ $INNERCOUNT -le 100 ]; do
			#echo $OUTERCOUNT
			./* $INNERCOUNT | awk 'BEGIN{print '"$OUTERCOUNT"';}{if(NR == 1){print $NF;} else if(NR == 6){print $(NF-1)}else {print $(NF-1)}}' | awk 'NR==1{x=$0;next}NF{x=x","$0}END{print x}' >> ../data/lab05_g10_data.csv
			let INNERCOUNT=INNERCOUNT+1
			done
		let OUTERCOUNT=OUTERCOUNT+1
	done
