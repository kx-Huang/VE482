#!/bin/bash

echo "Make sure to run this script under su!"
make clean
make all
insmod dicedevice.ko
echo "Rolling 2 dices!"
cat /dev/dice0
echo 7 > /dev/dice0
echo "Rolling 7 dices!"
cat /dev/dice0
echo 10 > /dev/dice0
echo "Rolling 10 dices!"
cat /dev/dice0
echo 30 > /dev/dice0
echo "Rolling 30 dices!"
cat /dev/dice0
echo "Rolling Back Gammon!"
cat /dev/dice1
echo "Rolling generic dice!"
cat /dev/dice2
rmmod -f dicedevice
echo "End of test! Below are the last 10 messages regarding dices..."
dmesg | grep "Dice" | tail -n 10
make clean
