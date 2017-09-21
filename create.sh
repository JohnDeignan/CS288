#!/bin/bash

# using command line arguments, create directories
# in either a depth or breadth first manner

breadth(){
local b=$1
local d=$2
local it=$3
local fil=$4
local temp=("${!5}")
local sep=0

if [ "${#lst[@]}" -eq "0" ] ; then
	for((i=0;i<b;i++)); do
		lst[$i]=$i
		mkdir "$fil-breadth/${lst[$i]}"
	done
else
	for i in "${temp[@]}"; do
		for((x=0;x<b;x++)); do
			lst[$sep]="$i/$x"
			mkdir "$fil-breadth/${lst[$sep]}"
			((sep++))
		done
	done
fi

for((i=0;i<${#lst[@]};i++)); do
	echo "$fil-breadth/${lst[$i]}"
done

((it++))
if [ "$it" -lt "$d" ]; then
	breadth $b $d $it $fil lst[@]
fi
}

depth(){
local b=$1
local d=$2
local fil=$3
local maxb=$((b-1))

for i in $(seq 0 $maxb); do
    if [ $d -eq 0 ]; then
	break
    fi
    mkdir $fil/$i
    depth $b $(expr $d - 1) $fil/$i
done
}

b=$1
d=$2
fil=$3
typ=$4
it=0
if [ "$typ" == "breadth" ]; then
	breadth $b $d $it $fil
elif [ "$typ" == "depth" ]; then
	depth $b $d $fil-depth
fi
