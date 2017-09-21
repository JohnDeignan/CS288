#!/bin/bash

main()
{
    local lst=(`ls $1`)
    echo Original: ${lst[@]}
    reverse lst[@]
}

reverse()
{
    local temp=("${!1}")
    count=${#temp[@]}
    ((count--))
    local rev=${temp[@]}
    for((i=0;i<count+1;i++)); do
	rev[$i]=${temp[$count-$i]}
    done
    echo Reversed: ${rev[@]}
}

main $1
