import os
import fcntl

class Lock: 
	def __init__(self, filename):
		self.filename = filename
		#This will create it if it does not exist already
		self.handle = open(filename, 'w')

		#Bitwise OR fcntl.LOCK_NB if you need a non-blocking lock 
	def acquire(self):
		fcntl.flock(self.handle, fcntl.LOCK_EX)
		print "acquire."

	def release(self):
		fcntl.flock(self.handle, fcntl.LOCK_UN)
		print "release."

	def __del__(self):
		self.handle.close()

import time
# Usage
try:
	lock = Lock("/tmp/lock_name.tmp")
	for i in range(10):
		lock.acquire()
		time.sleep(4)
# Do important stuff that needs to be synchronized
finally: 
	lock.release()

