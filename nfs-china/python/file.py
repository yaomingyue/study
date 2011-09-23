#!/usr/bin/python

import os
target = 'moon'
command = "mkdir %s" %target

os.system(command)

text = '''\
yaomon
sldf
sfdf
'''
file_name = raw_input('file_name:')
path = './moon/' + file_name
f = file(path, 'w')
f.write(text)
f.close()

