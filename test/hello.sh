#!/bin/bash

count=0

while :
do
	count=0
    sleep 3600
    while [ ${count} -lt 5 ]
    do
    	say "亲爱的， 休息一下吧， 摸摸大！"
		(( count++ ))
		sleep 1
    done
	say "摸啊"
done
