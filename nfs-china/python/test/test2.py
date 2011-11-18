#!/usr/bin/python

import os
import string
def average(intgerlist):
    sum1=0
    for i in intgerlist:
        sum1=sum1+i
    num=len(intgerlist)
    print sum1
    print len(intgerlist)

    return sum1/float(num)



print average([5,7,8])
print 3/4.0
