#! /bin/bash

date
if [ $# -eq 0 ]
then
echo "sleep 8 hours"
sleep 46800
else
echo "sleep" $1
sleep $1
fi
date

xdotool mousemove 430 100
sleep 5
xdotool mousemove 530 190
xdotool click 1
sleep 5
xdotool mousemove 230 210
sleep 15

xdotool mousemove 230 10
xdotool click 1
sleep 5

xdotool mousemove 700 130
xdotool click 1
sleep 15

xdotool mousemove 1000 570 
xdotool click 1
sleep 5


xdotool mousemove 370 280 
xdotool click 1
