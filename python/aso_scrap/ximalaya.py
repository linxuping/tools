# -*- coding: utf-8 -*-
import socket
import urllib2
import time
import sys
import os
import json
import struct
timeout=10
socket.setdefaulttimeout(timeout)
import xml.dom.minidom
import bs4
from bs4 import BeautifulSoup


def abstract(head):
	#head = "http://www.ximalaya.com/1072622/album/238347"
	urls = [head]

	headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}  
	def _get_doc(url):
		req = urllib2.Request(url, headers=headers)  
		socket = urllib2.urlopen(req)  
		ret = socket.read()
		return BeautifulSoup(ret, 'html.parser')
	def get_doc(url):
		for x in xrange(3):
			try:
				return _get_doc(url)
			except:
				pass
		return _get_doc(url)


	doc=get_doc(head)
	for ret in doc.find_all('a',class_='pagingBar_page'):
		#a = ret.a['href'].split('appid/')[1].split('/')[0]
		#b = ret.a.div.h5.string.split('.')[1]
		#c = ret.a.div.find_all('h6')[1].find_all('span')[0].string
		#d = ret.a.div.find_all('h6')[1].find_all('span')[1].string.strip('+')
		url = "http://www.ximalaya.com"+ret['href']
		if 'album' not in url:
			continue
		if not url in urls:
			urls.append(url)

	print urls
	for url in urls:
		doc=get_doc(url)
		print url
		for ret in doc.find_all('a',class_='title'):
			if not 'href' in ret.attrs:
				continue
			link = ret['href']
			title = ret['title']
			if not 'sound' in link:
				continue
			voice = link.rsplit('/',2)[-1]
			#print voice
			doc2=str(get_doc('http://m.ximalaya.com/tracks/%s.json'%voice))
			#if '2005457' == voice:
			#	print str(doc2)
			if '"play_path":"' in doc2:
				print title,doc2.split('"play_path":"')[1].split('"',2)[0]


abstract("http://www.ximalaya.com/1072622/album/238347")
