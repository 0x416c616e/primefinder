#!/usr/bin/env bash
COUNT=$(ls | grep gaps_ | wc -l | tr -d '\n')
COUNT=$(($COUNT-1))
FILESIZE=50000
if [ $COUNT -le 0 ]
then
	echo "error: need more data in order to graph distribution"
	exit 1
fi

LASTRUN=$(cat last_was_completed.txt | tr -d '\n')
if [ $LASTRUN == "false" ]
then
	#this means the last file is incomplete and should be disregarded
	COUNT=$(($COUNT-1))
fi


for (( i=0; i<=$COUNT; i++ ))
do
	NAME=$"gaps_$i.dat"
	OFFSET=$(($i*$FILESIZE))
	NUMPRIMES=$(cat $NAME | wc -l | tr -d '\n')
	echo $OFFSET, $NUMPRIMES
done
