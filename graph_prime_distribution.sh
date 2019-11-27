#!/usr/bin/env bash
FILE_EXISTS=$(cat distribution_graphed.txt | tr -d '\n')
echo $FILE_EXISTS
SCRIPTFILE="prime_distribution_script.p"
if [ $FILE_EXISTS == "true" ]
then
	echo -n "" > $SCRIPTFILE
	echo "set terminal png size 800,800" >> $SCRIPTFILE
	echo "set output 'primedistribution.png'" >> $SCRIPTFILE
	echo "set title 'Prime Distribution'" >> $SCRIPTFILE
	echo "unset key" >> $SCRIPTFILE
	echo "set datafile separator comma" >> $SCRIPTFILE
	echo -n "plot 'prime_distribution.dat'" >> $SCRIPTFILE
	echo " with lines lc rgb \"purple\"" >> $SCRIPTFILE
	gnuplot $SCRIPTFILE
	echo "Saved new graph to primedistribution.png"
	echo "true" > distribution_graphed.txt
fi



