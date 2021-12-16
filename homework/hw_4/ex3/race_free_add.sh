#!/bin/bash
FILE=./race_free.out
if ! [ -s $FILE ]; then
    echo 0 >> $FILE
fi
for i in {1..100} do
    (
        flock -n 200
        number=$(tail -n 1 $FILE)
        ((number++))
        echo $number >> $FILE
    ) 200>> $FILE
done
