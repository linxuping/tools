# -*- coding: utf-8 -*-  
import os
import sys
import commands
import json
import time
import pika
import urllib2
import mylog as mo
import traceback
import socket
socket.setdefaulttimeout(60)
urllib2.socket.setdefaulttimeout(60) 

class RMQ_Manager:
	def __init__(self, _exchange, _qname):
		self.exchange = _exchange
		self.qname = _qname
		self.initconn()
	def initconn(self):
		credentials = pika.PlainCredentials('teiron', 'teiron')
		connection = pika.BlockingConnection(pika.ConnectionParameters(host='192.168.12.200', credentials=credentials))
		self.channel = connection.channel() 
		self.declare()
	def declare(self):
		pass
	def send(self, msg):
		pass
	def dispatch(self):
		pass
		

#rabbitmq with durable and priority.
class RMQ_DPManager(RMQ_Manager):
	def __init__(self, _exchange, _qname):
		RMQ_Manager.__init__(self, _exchange, _qname)
	def initconn(self):
		RMQ_Manager.initconn(self)
	def declare(self):
		self.channel.exchange_declare(exchange=self.exchange,type='topic',durable=True)
		self.channel.queue_declare(queue=self.qname, durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
		self.channel.queue_bind(exchange=self.exchange, queue=self.qname, routing_key=self.qname)
	def send(self, msg):
		self.channel.basic_publish(exchange=self.exchange,routing_key=self.qname,body=msg,
			properties=pika.BasicProperties(
			delivery_mode=2,priority=5, # make message persistent
		))
	def dispatch(self):
		while 1: #blocked reactor
			cont = None
			try:
				self.declare()
				r = self.channel.basic_get(queue=self.qname, no_ack=False) #0
				if r[0] != None:
					self.channel.basic_nack(delivery_tag=r[0].delivery_tag, multiple=False, requeue=False)
					cont = r[-1]
					#print "send sms:  ",r[-1]#, r[0].delivery_tag
					#process m3u8, get mp4 and download
					self.handler(cont)
			except:
				mo.logger.error( str(sys.exc_info()) + "; " + str(traceback.format_exc()) )
				self.initconn()
				if cont != None:
					mo.logger.warning("Put back queue: %s"%cont)
					self.send(cont)
			time.sleep(1)
	@staticmethod
	def register_and_run(_exchange, _qname, _handler):
		g_rmq_mgr = RMQ_DPManager(_exchange, _qname)
		g_rmq_mgr.handler = _handler		
		g_rmq_mgr.dispatch()

		
		
		