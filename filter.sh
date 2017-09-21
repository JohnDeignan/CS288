#!/bin/bash

main()
{
    local fileName=(`ls $1`)
    local count=${#fileName[@]}
    local fileSize=${fileName[@]}
    for ((i=0;i<count;i++)); do
	fileSize[$i]=$(stat -c%s ${fileName[$i]})
    done
    average $count fileSize[@] fileName[@]
}
average()
{
    local count=$1
    local fileSize=("${!2}")
    local fileName=("${!3}")
    sizeTotal=0
    for i in ${fileSize[@]}; do
	let sizeTotal+=$i
    done
    local ave=$((sizeTotal/count))
    filter $ave $count fileName[@] fileSize[@]
}
filter()
{
    local ave=$1
    local count=$2
    local fileName=("${!3}")
    local fileSize=("${!4}")
    local filteredFiles=${fileName[@]}
    x=0
    for ((i=0;i<count;i++)); do
	if((fileSize[i]>$ave)); then
	    filteredFiles[x]=${fileName[$i]}
	    ((x++))
	fi
    done
    echo File Names: ${fileName[@]}
    echo File Sizes: ${fileSize[@]}
    echo Average Size: $ave
    echo Filtered Files: ${filteredFiles[@]}
	  
}
main $1
