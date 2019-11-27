#!/usr/bin/env bash
#this shell script will run the primegap program again and again
#you might have to change it slightly for linux or macOS because this was made for Windows
while :
do
	echo "---------------------------------------------"
	echo "---------------------------------------------"
	MESSAGE="HOLD ctrl+c DOWN for a few seconds if you want to quit"
	echo $MESSAGE
	echo "Running prime gap 50k run..."
	./primegaps.exe
	echo "Finished running a 50k prime gap run."
	echo "Running prime gap grapher..."
	echo $MESSAGE
	./graph_prime_gaps.sh
	echo "Finished graphing prime gaps."
	echo $MESSAGE
	echo "Finding prime number distribution..."
	./prime_distribution.sh
	echo "Done finding prime number distribution."
	echo $MESSAGE
	echo "Graphing prime number distribution..."
	./graph_prime_distribution.sh
	echo "Finished graphing prime number distribution."
	echo $MESSAGE
	sleep 1
done
