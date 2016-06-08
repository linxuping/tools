#!/usr/bin/env python 
# -*- coding: utf-8 -*-
import mylog as mo
import os
import time

def check_disk(rate):
	ret = -1
	try:
		ret = int(os.popen('df').read().split("% /mnt")[0].rsplit('  ',1)[1])
	except:
		mo.logger.error("check_disk failed: %s"%str(str(sys.exc_info()) + "; " + str(traceback.format_exc())) )
	if ret < rate:
		return True
	return False
	

	
	
def run_block_if_excceed(rate, seconds):
	while not check_disk(rate):
		mo.logger.warn("run_block_when_excceed. rate:%d, wait for %ds"%(rate,seconds) )
		time.sleep(seconds)
		pass
