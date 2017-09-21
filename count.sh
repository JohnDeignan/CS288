#!/bin/bash

for x in {a..z}; do
    lst=(`ls /bin/$x*`)
    count=${#lst[@]}
    echo $x $count
done
