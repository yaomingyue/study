#!/bin/bash

echo -n "find the gps node1 :"
ls /dev/ttyS1
echo -n "find the gps node2 :"
ls /dev/ttyS2
echo "………………………………done"
echo -n "find the gps daemon :"
ls /usr/libexec/gypsy-daemon
echo "………………………………done"
#minicom -s
#sudo /usr/libexec/gypsy-daemon --help
#sudo /usr/libexec/gypsy-daemon --no-daemon --nmea-log "stdout"
sudo echo "pu port             /dev/ttyHS2" > /ect/minirc.dfl

kill -9 $(ps -ef|grep 进程名关键字|gawk '$0 !~/grep/ {print $2}' |tr -s '\n' ' ')

