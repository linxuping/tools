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

qname_packet = "jb_down_gather7213"
q_host = "100.84.72.113"

qname_upload = "jb_down_%s"%socket.gethostname()

import ctypes
import platform

def get_free_space_mb(folder):
    """ Return folder/drive free space (in bytes)
    """
    if platform.system() == 'Windows':
        free_bytes = ctypes.c_ulonglong(0)
        ctypes.windll.kernel32.GetDiskFreeSpaceExW(ctypes.c_wchar_p(folder), None, None, ctypes.pointer(free_bytes))
        return free_bytes.value/1024/1024/1024 
    else:
        st = os.statvfs(folder)
        return st.f_bavail * st.f_frsize/1024/1024

g_rmq_mgr = mo.RMQ_DPManager("app_collect",qname_packet)
g_rmq_mgr_up = mo.RMQ_DPManager("app_collect",qname_upload)
mo.RMQ_DPManager("app_collect", "jb_crack_%s"%socket.gethostname())
mo.RMQ_DPManager("app_collect", "jb_blktest_%s"%socket.gethostname())

def jb_pkg_down(pkgurl, itemid, versionextid):
	if not pkgurl.endswith(".ipa"):
		mo.logger.error("error pkg url: %s"%pkgurl)
		return False
	pkgname = pkgurl.rsplit("/",1)[1]
	fpkg = urllib2.urlopen(pkgurl)
	f = open(pkgname, "wb+")
	#buf = fpkg.read()	
	_len = 0
	while 1:
		s = fpkg.read(1024*512)
		if len(s) == 0:
			break
		f.write(s)
		_len += len(s)
	#f.write(buf)
	f.close()
	mo.logger.info("%s %s ipa downloaded. size:%d %s.ipa"%(itemid,versionextid,_len,pkgname))

g_jb_pkgs_max = 30
g_space_min = 5
def jb_down(qdata, pri):
	itemid, = struct.unpack("I", qdata[0:4])
	versionextid, = struct.unpack("I", qdata[4:8])
	print "%s_%s qlen:%d"%(itemid,versionextid,g_rmq_mgr.get_qlen())
	mo.logger.info("%s_%s"%(itemid,versionextid)) 
	time.sleep(2)
	einfo = ""
	for i in range(2):
		try:
			jb_pkg_down("http://%s/%s_%s.ipa"%(q_host,itemid,versionextid),itemid,versionextid)
			g_rmq_mgr_up.send(qname_upload, qdata, pri)
			break
		except:
			einfo = "jb_down Error: %s"%str(str(sys.exc_info()) + "; " + str(traceback.format_exc())) 
	if einfo != "":
		print einfo
		mo.logger.error( "jb_down Error: %s"%str(str(sys.exc_info()) + "; " + str(traceback.format_exc())) )
		g_rmq_mgr_up.put_back_queue(qdata,pri)
	count = 1
	while True:
		space = int(get_free_space_mb('C:\\'))
		if g_rmq_mgr_up.get_qlen()>g_jb_pkgs_max or space<g_space_min:
			time.sleep(1)
			count += 1
			if count%60 == 0:
				mo.logger.warn("busy and wait %d min."%(count/60)) 
			elif space<g_space_min:
				mo.logger.warn("space less than %dG."%g_space_min) 
				print "space less than %dG."%g_space_min
		else:
			break
	


g_rmq_mgr.handler_register(jb_down)		
g_rmq_mgr.dispatch()





