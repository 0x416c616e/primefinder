#!/usr/bin/env bash
COUNT=$(ls | grep gaps_ | wc -l | tr -d '\n')
COUNT=$(($COUNT-1))
FILESIZE=50000
for (( i=0; i<=$COUNT; i++ ))
do
	NAME=$"gaps_$i.csv"
	OFFSET=$(($i*$FILESIZE))
	NUMPRIMES=$(cat $NAME | wc -l | tr -d '\n')
	echo $OFFSET, $NUMPRIMES
done
