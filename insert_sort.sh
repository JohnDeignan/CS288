#!/bin/bash

sorted=("$@")
total=${#sorted[@]}

for((i=1;i<total;i++)); do
    temp=${sorted[i]}
    x=$((i-1))
    while((temp<sorted[x])); do
	sorted[x+1]=${sorted[x]}
	((x--))
	if((x==-1)); then
	    break
	fi
    done
    sorted[x+1]=$temp
done
   
echo ${sorted[@]}
