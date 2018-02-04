# -*- coding: utf-8 -*-

import time
from time import sleep
from TwitterAPI import TwitterAPI
import struct
import os
from serial import Serial
import httplib
from httplib import IncompleteRead

from auth_romforlek import (
    consumer_key,
    consumer_secret,
    access_token,
    access_token_secret
)


microbitPort = '/dev/tty.usbmodem1422' # USB port address for the micro:bit /dev/ttyACM0 or /dev/tty.usbmodem40132 or similar
microbitBaud = '115200' # Baud for serial communication
microbitWaitTime = 0.001 # The length of time Python wait before attemping to issue commands to the micro:bit
stringToTrack = "#trump" # Change this to the search term you wish to track from Twitter
tweet_number = 0
count = 0
skip = 0
neopixel = 12
neo = 0

#sleep(microbitWaitTime)

ser = Serial(microbitPort, microbitBaud, timeout=3)
api = TwitterAPI(consumer_key, consumer_secret, access_token, access_token_secret)

print 'Twitter ready!'

r = api.request('statuses/filter', {'track':stringToTrack})
#r = api.request('statuses/filter', {'locations':'9.7524,59.3785,11.697,60.4341'})
for item in r.get_iterator():
    if 'text' in item:
        #tweet = item['text'].encode('utf-8').strip(stringToTrack)
        ser.write("t")
        tweet_number = tweet_number + 1
        neo = neo + 1
        print tweet_number
        print ("Neo:" + str(neo))
        if neo == neopixel:
            neo = 0
            ser.write("neo")
        #print tweet
        #print('-------------------')
        #print('')
        #sleep(microbitWaitTime)
    elif 'limit' in item:
        skip = item['limit'].get('track')
        print('*** SKIPPED %d TWEETS' % skip)
        ser.write("#")
#    elif 'disconnect' in item:
#        print('[disconnect] %s' % item['disconnect'].get('reason'))
#        break
    #print(tweet_number+skip);

