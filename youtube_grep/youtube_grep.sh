#!/bin/bash

$cat>views.txt
$cat>names.txt
$cat>times.txt
$cat>titles.txt
$cat>keys.txt

egrep -o "[0-9,]+(,[0-9]+) views" index.html | while read i; do
	views=`expr "$i" : "\([0-9,]*\)"`
	echo ${views//,/} >> views.txt; done

grep -o "a href=\"/user.*\" >[a-zA-Z0-9]\(.*\).*<\/a>\|a href=\"/channel.*\" >[a-zA-Z0-9]\(.*\).*<\/a>" index.html | while read i; do
	name=`expr "$i" : ".*\" >\(.*\).*<\/a>"`
	echo $name >> names.txt; done

egrep -o "Duration: [0-9]*[:][0-9][0-9]" index.html | while read i; do
        time=`expr "$i" : '.*\(..[0-9]*[:][0-9][0-9]\)'`
	echo $time >> times.txt; done

grep -o "title=\"\(.*\).*\" aria-describedby" index.html | while read i; do
	titles=`expr "$i" : ".*title=\"\(.*\).*\" aria-describedby"`
	echo $titles >> titles.txt; done

grep -o "a href=\"/watch?v=[-a-zA-Z0-9\_]*" index.html | while read i; do
	key=`expr "$i" : '.*?v=\([-a-zA-Z0-9|_ ]*\)'`
	echo $key >> keys.txt; done

sed -i 's/\&amp;/\&/g' *.txt
sed -i "s/\&\#39;/\'/g"  *.txt 
sed -i 's/\&quot;/(quotes)/g' *.txt
paste -d\; views.txt names.txt times.txt titles.txt keys.txt > all.csv
