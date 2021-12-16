#!/bin/bash
FILE=./race.out
if ! [ -s $FILE ]; then
    echo 0 >> $FILE
fi
for i in {1..100} do
    number=$(tail -n 1 $FILE)
    ((number++))
    echo $number >> $FILE
done

