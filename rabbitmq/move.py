#!/usr/bin/python
# -*- coding: utf-8 -*-
from biplist import *
import os
import sys
import urllib2
import traceback
import modules as mo
import socket
import struct
import time
import ctypes
import platform



g_rmq_mgr = mo.RMQ_DPManager("exchange","testq1")
g_rmq_mgr2 = mo.RMQ_DPManager("exchange","testq2")


tmplist = []
def insert_back(qdata, pri):
	if qdata not in tmplist:
		tmplist.append(qdata)
		g_rmq_mgr2.put_back_queue(qdata,pri)
	else:
		print qdata
	return

	if pri >= 3:
			g_rmq_mgr2.put_back_queue(qdata,pri)
	else:
			pass#g_rmq_mgr3.put_back_queue(qdata,pri)
	return
	if qdata in tmplist:
		print "---- ",qdata
	else:
		tmplist.append(qdata)
		g_rmq_mgr2.put_back_queue(qdata,pri)
	return
	itemid, = struct.unpack("I", qdata[0:4])
	versionextid, = struct.unpack("I", qdata[4:8])
	g_rmq_mgr2.put_back_queue("%s_%s"%(itemid,versionextid),pri)
	return

		


g_rmq_mgr.handler_register(insert_back)		
g_rmq_mgr.dispatch()





