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
		credentials = pika.PlainCredentials('***', '***')  #to teiron
		connection = pika.BlockingConnection(pika.ConnectionParameters(host='192.168.12.200', credentials=credentials))
		self.channel = connection.channel() 
		self.declare()
	def declare(self):
		pass
	def send(self, qname, msg, pri):
		pass
	def dispatch(self):
		pass
		

#rabbitmq with durable and priority.
class RMQ_DPManager(RMQ_Manager):
	def __init__(self, _exchange, _qname):
		RMQ_Manager.__init__(self, _exchange, _qname)
	def initconn(self):
		try:
			RMQ_Manager.initconn(self)
		except:
			mo.logger.error("initconn failed: %s"%str(str(sys.exc_info()) + "; " + str(traceback.format_exc())))
	def declare(self):
		self.channel.exchange_declare(exchange=self.exchange,type='topic',durable=True)
		self.channel.queue_declare(queue=self.qname, durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
		self.channel.queue_bind(exchange=self.exchange, queue=self.qname, routing_key=self.qname)
	def get_qlen(self):
		return int(self.channel.queue_declare(queue=self.qname, durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10}).method.message_count)
	def send(self, qname, msg, pri):
		for i in xrange(3):
			try:
				self.channel.basic_publish(exchange=self.exchange,routing_key=qname,body=msg,
					properties=pika.BasicProperties(
					delivery_mode=2,priority=pri, # make message persistent
				))
				mo.logger.info("Put queue %s: %s"%(qname,msg) )
				break
			except:
				mo.logger.error("Put queue failed: %s"%str(str(sys.exc_info()) + "; " + str(traceback.format_exc())))
				self.initconn()
		return True
	def put_back_queue(self, cont, pri):
		if cont != None:
			mo.logger.warning("Put back queue: %s"%cont)
			self.send(self.qname, cont, pri)
	def dispatch(self):
		while 1: #blocked reactor
			cont = None
			r = None
			pri = 3
			try:
				self.declare()
				r = self.channel.basic_get(queue=self.qname, no_ack=False) #0
				if r[0] != None:
					self.channel.basic_nack(delivery_tag=r[0].delivery_tag, multiple=False, requeue=False)
					cont = r[-1]
					print "send sms:  ",r[1].priority#, r[0].delivery_tag
					pri = r[1].priority
					#process m3u8, get mp4 and download
					self.handler(cont, pri)
			except:
				mo.logger.error( str(sys.exc_info()) + "; " + str(traceback.format_exc()) )
				self.initconn()
				self.put_back_queue(cont, pri)
			#finally:
				#print r.__dict__
				#if r != None:
				#	self.channel.basic_ack(r.delivery_tag)  
			time.sleep(1)
	def handler_register(self, _handler):
		self.handler = _handler
	@staticmethod
	def register_and_run(_exchange, _qname, _handler):
		g_rmq_mgr = RMQ_DPManager(_exchange, _qname)
		g_rmq_mgr.handler_register(_handler)		
		g_rmq_mgr.dispatch()

		
		
		
