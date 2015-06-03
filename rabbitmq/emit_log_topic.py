#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''Usage
'''
import pika
import sys

credentials = pika.PlainCredentials('test_user', 'test_user')
connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost', credentials=credentials))
channel = connection.channel()

channel.exchange_declare(exchange='topic_logs',
                         type='topic')
#channel.queue_declare(queue='linxpq', durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
channel.queue_declare(queue='linxpq1', durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
channel.queue_declare(queue='linxpq2', durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
channel.queue_bind(exchange='topic_logs', queue='linxpq1', routing_key="zb.*")
channel.queue_bind(exchange='topic_logs', queue='linxpq2', routing_key="zb")

'''
routing_key = sys.argv[1] if len(sys.argv) > 1 else 'anonymous.info'
message = ' '.join(sys.argv[2:]) or 'Hello World!'
channel.basic_publish(exchange='topic_logs',
                      routing_key=routing_key,
                      body=message,
		      properties=pika.BasicProperties(
                         priority = 9, # make message persistent
                      ))
'''
import time
for i in range(3):
    channel.basic_publish(exchange='topic_logs',
                      routing_key='zb.yy',
                      body=u'你好!world. 4',
		      properties=pika.BasicProperties(
                         priority = 4, # make message persistent
                      ))
    channel.basic_publish(exchange='topic_logs',
                      routing_key='zb.yy3',
                      body=u'你好!world. 5',
		      properties=pika.BasicProperties(
                         priority = 5, # make message persistent
                      ))
    channel.basic_publish(exchange='topic_logs',
                      routing_key='zb',
                      body=u'你好!world. 8',
		      properties=pika.BasicProperties(
                         priority = 8, # make message persistent
                      ))
    channel.basic_publish(exchange='topic_logs',
                      routing_key='zb',
                      body=u'你好!world. 9',
		      properties=pika.BasicProperties(
                         priority = 9, # make message persistent
                      ))
    print i
#print " [x] Sent %r:%r" % (routing_key, message)
#print "fini."
connection.close()
