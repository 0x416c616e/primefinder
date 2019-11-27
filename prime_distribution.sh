#!/usr/bin/env bash
COUNT=$(ls | grep gaps_ | wc -l | tr -d '\n')
COUNT=$(($COUNT-1))
FILESIZE=50000
FILENAME="prime_distribution.dat"

#clear the old file
echo -n "" > $FILENAME

#check if there's enough data
if [ $COUNT -le 0 ]
then
	#if there is insufficient data, it can't be graphed
	echo "error" > $FILENAME
	exit 1
fi

#check if last run was ended before finishing, resulting in the last
#file being incomplete
#but will still use the finished data
LASTRUN=$(cat last_was_completed.txt | tr -d '\n')
if [ $LASTRUN == "false" ]
then
	#this means the last file is incomplete and should be disregarded
	COUNT=$(($COUNT-1))
fi


#save to file
for (( i=0; i<=$COUNT; i++ ))
do
	NAME=$"gaps_$i.dat"
	OFFSET=$(($i*$FILESIZE))
	NUMPRIMES=$(cat $NAME | wc -l | tr -d '\n')
	echo $OFFSET, $NUMPRIMES >> $FILENAME
done

#mark that a prime distribution file has been created
echo "true" > distribution_graphed.txt
