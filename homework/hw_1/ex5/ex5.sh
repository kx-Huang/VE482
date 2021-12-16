#!/bin/sh
useradd -m michael
ps -ael
cat /proc/cpuinfo
cat /proc/meminfo
head -n 666 /dev/random | tee 1.out > 2.out
cat 1.out 2.out > 3.out
hexdump 3.out
find /usr/src -name '*semaphore*' | xargs grep -lw 'ddekit_sem_down'