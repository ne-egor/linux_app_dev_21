#!/bin/bash

TIME=${1:-0.01}
COL=0
LIN=0

tput clear

while IFS= read line
do
        COL=0
        for i in $(xxd -c 1 <<< $line | cut -d' ' -f2):
        do
                if [ $i != 20 ]
                then
                        echo $LIN $COL $i 
                fi
                (( COL ++ ))
        done
        (( LIN ++ ))
done | 
shuf |
while read LIN COL c
do
        tput cup $LIN $COL
        xxd -r -p <<< $c
        sleep $TIME
done

tput cup $(tput lines) 0
