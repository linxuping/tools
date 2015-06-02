#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

channel.queue_declare(queue='')
channel.queue_bind(exchange='amq.direct',queue='',routing_key='test')

print '文件 for test'
print ' [*] Waiting for messages. To exit press CTRL+C'

def callback(ch, method, properties, body):
    print u" [x] Received %s" % body.decode("utf-8")

channel.basic_consume(callback,
                      queue='',
                      no_ack=True)

channel.start_consuming()

