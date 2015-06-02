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

channel.queue_declare(queue='')

channel.basic_publish(exchange='amq.direct',
                      routing_key='test',
                      body=u'你好!world.')
print u" [x] Sent '你好!world.'"
connection.close()

