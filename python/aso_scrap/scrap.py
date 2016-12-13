# -*- coding: utf-8 -*-
import socket
import urllib2
import time
import sys
import os
import struct
timeout=30
socket.setdefaulttimeout(timeout)
import xml.dom.minidom
import bs4
from bs4 import BeautifulSoup
print 'old encoding value:', sys.getdefaultencoding()
reload(sys)
sys.setdefaultencoding('utf-8')
print 'new encoding value:', sys.getdefaultencoding()

class Queue_client :
	__host = "121.41.6.153"
	__port = 61021
	#__timeout = 15

	def __init__(self, host="", port="", timeout="") :
		if host :
			self.__host = str(host)
		if port :
			self.__port = int(port)
		#if timeout:
		#	self.__timeout = int(timeout)
		
		self.__client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.__client.setsockopt( socket.SOL_SOCKET, socket.SO_REUSEADDR, 1 )
		#self.__client.bind(('0.0.0.0', 12345))
		addr = (self.__host, self.__port)
		if self.__client.connect_ex(addr) != 0:
			connect_fail = True
			for i in range(8):
				if self.__client.connect_ex(addr) == 0:
					connect_fail = False
					break
				print "try ",i
				time.sleep(2)
			if connect_fail: 
				raise Exception("Queue connect fail")

	def close(self) :
		self.__client.close()


	def get_ip(self) :
		bin_str = struct.pack("2H2I4B", 16, 7, 3628618852, 0, 0XFF,0XFF,0XFF,0XFF) 
		#100.84.72.216
		self.__client.send(bin_str)
		res = None
		try:
			total_length, = struct.unpack("I", self.__client.recv(4))
			ip_int, = struct.unpack("I", self.__client.recv(4))
			#ip = socket.inet_ntoa(struct.pack('I',socket.htonl(ip_int)))
			ip = socket.inet_ntoa(struct.pack("=I", ip_int))
			timeout, = struct.unpack("I", self.__client.recv(4))
			print ip,timeout
			return ip
		except Exception, e :
			return res


	def __del__(self) :
		self.close()
'''		
qc = Queue_client()
print qc.get_ip()
time.sleep(3000)
'''		

		
		
def cu(s):
  if type(s) == bs4.element.NavigableString:
    return s.string
  return s.encode("utf-8")



urls=[
"http://lxp100.com/rank/float/float/up/country/cn/device/iphone/brand/free/genre/36",
]

items = []
f = open("aso_%s.txt"%(time.strftime('%m-%d_%H')),"w+")
count = 0
while True:
	count+=1
	for _v in urls:
		print _v
		for i in range(3):
			try:
				#req=urllib2.Request(_v)
				qc = Queue_client()
				ip = qc.get_ip()
				proxyConfig = 'http://%s:%s@%s' % ('mpxy', 'pp25pp', '%s:62020'%ip) 
				#resp=urllib2.urlopen(req,proxies={'http':proxyConfig})
				handler = urllib2.ProxyHandler({'http' : proxyConfig})
				opener = urllib2.build_opener(handler)
				resp = opener.open(_v)
				doc=BeautifulSoup(resp.read(), 'html.parser')
				isok = False
				for ret in doc.find_all('div',class_='thumbnail'):
					a = ret.a['href'].split('appid/')[1].split('/')[0]
					b = ret.a.div.h5.string.split('.')[1]
					c = ret.a.div.find_all('h6')[1].find_all('span')[0].string
					d = ret.a.div.find_all('h6')[1].find_all('span')[1].string.strip('+')
					try:
						item = u"%s\t%s\t%s\t%s\t%s\t%d"%(cu(a),cu(b),cu(c),cu(d),_v,count)
						item_check = u"%s\t%s"%(cu(a),_v)
						if item_check not in items:
							f.write("%s\t%s\n"%(item,time.strftime('%m-%d %H')))
							items.append(item_check)
					except:
						pass #print u"%s    _    %s    %s"%(cu(a),cu(c),cu(d))
					isok = True
				if isok:
					break
				else:
					print "no ok."
					#os.system("Rasdial adsl /DISCONNECT")
					time.sleep(20)
			except:
				print sys.exc_info()
		time.sleep(20)
		f.flush()
f.close()
import time
time.sleep(3000)
