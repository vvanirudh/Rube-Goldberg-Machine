#!/bin/bash
COUNT=1000
RERUN=1
cd bin
while [ $COUNT -le 10000 ]; do
	RERUN=1
	while [ $RERUN -le 10 ]; do
		./cs296_base $COUNT > temp
		mv gmon.out $COUNT-$RERUN.out
		let RERUN=RERUN+1
	done
	let COUNT=COUNT+1000
done
gprof cs296_base *.out > ../data/g10_debug_prof.dat
rm -rf *.out
rm -rf temp
cd ..
python gprof2dot.py data/g10_debug_prof.dat | dot -Tpng -o data/g10_debug_prof.png
