#!/usr/bin/python

import os
import string
def allVowels(string):
    k=0
    print string
    for str1 in string:
        if str1 == 'a' or str1 == 'e' or str1 == 'i' or str1 == 'o' or str1 == 'u':
            k=k+1
    
    return k
print "hello"
#allVowels("abcdefgh")
while 1:
    str2=raw_input('please input :')
    print allVowels(str2)


