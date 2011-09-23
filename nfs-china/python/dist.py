#!/usr/bin/python

ab = {
        'baidu' : 'www.baidu.com',
        'youku' : 'www.youku.com',
        'google': 'www.google.com.hk',
     }

print ab['baidu'] 
print ab 

ab['qzone'] = 'www.qzone.com'

del ab['baidu']

print ab 



