#!/usr/bin/python

import os
import sys
import random
import time

guess_num=random.randint(1,100)

while 1:
    my_num=int(raw_input('input your num :'))

    if guess_num > my_num:
        print "it is too low"
    if guess_num < my_num:
        print "it is too high"
    if guess_num == my_num: 
        print "it is right on"
        sys.exit(0)
    
    print " please again"
    time.sleep(1)


