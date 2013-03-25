#!/usr/bin/python

shoplist = ['apple', 'mango', 'carrot', 'banana']

print len(shoplist)

for item in shoplist:
    print item

shoplist.append('rice')

print shoplist 

del shoplist[2]
shoplist.sort()
print shoplist 

numlist = [1, 2, 3, 4]

print numlist 
print numlist[2] + numlist[1] 



