#!/usr/bin/python

import os
import string

def toBinary(intvalue):
    mylist=[0] 
    while 1:
        if intvalue%2:
            num=1
        else:
            num=0
        mylist.append(num)
        intvalue=intvalue/2
        if intvalue == 0:
            return mylist

while 1:
    str2=raw_input('please input :')

    kklist=toBinary(int(str2))
    for i in kklist[-1:0:-1]:
       os.write(1,"%d" %i)
    print ""

    

