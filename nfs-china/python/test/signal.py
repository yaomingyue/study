#!/usr/bin/python

import os
import string
import signal
import time
import sys

def myexit(signalNum,e):
    #print 'signalNum: %s' %(signalNum)
    #print 'e:%s ' %(e)
    print "this program will exit"
    sys.exit(0)

signal.signal(signal.SIGINT, myexit)

while 1:
    print "heooooooo"
    time.sleep(1)


