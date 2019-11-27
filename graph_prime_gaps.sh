#!/usr/bin/env bash

#this script creates a script for generating
#the prime gap graph in gnuplot
#you will need to have gnuplot installed
#and on windows, you will need to have gnuplot added to your path variable
#if you can't use gnuplot at the command line, it means you need to
#uninstall gnuplot and reinstall it, but this time check the box
#that adds gnuplot to your path variable

echo -n "" > prime_gap_script.p

echo "set terminal png size 800,800" >> prime_gap_script.p
echo "set output 'primegaps.png'" >> prime_gap_script.p
echo "set title 'Prime Gaps'" >> prime_gap_script.p
echo "unset key" >> prime_gap_script.p
echo "set datafile separator comma" >> prime_gap_script.p

#number of gaps_X.dat files in the directory
COUNT=$(ls | grep gaps_ | wc -l | tr -d '\n')

#starts with zero so subtract one
#i.e. 10 files means gaps_0.dat to gaps_9.dat
COUNT=$(($COUNT-1))


VERYFIRSTPART="plot "
FIRSTPART="'gaps_"
AFTER=".dat' with lines lc rgb \"purple\""

for (( i=0; i<=$COUNT; i++ ))
do
	FILENAME=""
	if [ $i == 0 ]
	then
		FILENAME+=$VERYFIRSTPART
	fi
	FILENAME+="$FIRSTPART$i$AFTER"
	if [ $i -lt $COUNT ]
	then
		FILENAME+=", \\"
	fi
	echo $FILENAME >> prime_gap_script.p
done

gnuplot prime_gap_script.p

echo "Saved new graph to primegaps.png"
