#!/usr/bin/env bash
#this shell script will run the primegap program again and again
#you might have to change it slightly for linux or macOS because this was made for Windows
while :
do
	MESSAGE="HOLD ctrl+c DOWN for a few seconds to quit"
	echo $MESSAGE
	./primegaps.exe
	echo $MESSAGE
	./graph_prime_gaps.sh
	sleep 1
done
