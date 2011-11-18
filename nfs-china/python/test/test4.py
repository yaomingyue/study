#!/usr/bin/python

import os
import string

def complex(str1):
    ret=True
    num=len(str1)
    for i in range(0,num-1):
        if str1[i] != str1[num-1-i]:
            ret=False
    return ret

while 1:
    str2=raw_input('please input:')
    print complex(str2)
        

            

        

