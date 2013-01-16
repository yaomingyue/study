#!/usr/bin/python 

import time

t = time.time()

while True:
    t_1 = time.time()

    if t_1 - t > 10:
        print 'ten seconds'
        break
