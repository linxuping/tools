#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''DESC: unicode support
RECV: 
  ./examples/amqp_listen localhost 5672 amq.direct test python simple_test_send_1.py 
  run in linux.
SEND: 
  python simple_test_send_1.py 
  run in remote windows.
'''
import pika

credentials = pika.PlainCredentials('test_user', 'test_user')
connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='192.168.29.131', credentials=credentials))
channel = connection.channel()

channel.queue_declare(queue='linxpq', durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})

import time
for i in range(3):
    channel.basic_publish(exchange='',
                      routing_key='linxpq',
                      body=u'你好!world. 9',
		      properties=pika.BasicProperties(
                         priority = 9, # make message persistent
                      ))
    channel.basic_publish(exchange='',
                      routing_key='linxpq',
                      body=u'你好!world. 5',
		      properties=pika.BasicProperties(
                         priority = 5, # make message persistent
                      ))
    channel.basic_publish(exchange='',
                      routing_key='linxpq',
                      body=u'你好!world. 8',
		      properties=pika.BasicProperties(
                         priority = 8, # make message persistent
                      ))
    print i
print u" [x] Sent '你好!world.'"
connection.close()

