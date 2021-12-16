#!/bin/sh
select i in Mon Tue Wed
do
  echo -ne "You choose: "
  case $i in
    Mon) echo "Monday";;
    Tue) echo "Tuesday";;
    Wed) echo "Wednesday";;
    *) echo nothing;;
  esac
  break
done