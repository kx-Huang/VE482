#!/bin/sh
ans=$((($RANDOM)%100))
guess=100
while true ; do
    while true ; do
        read -p "Guess a number: " guess
        if [[ $guess =~ ^[0-9]+$ ]] ; then
            break
        fi
    done
    if [ $ans -lt $guess ] ; then
        echo "Smaller"
    elif [ $ans -gt $guess ] ; then
        echo "Larger"
    else
        echo "You win! The number is" $ans
        break
    fi
done