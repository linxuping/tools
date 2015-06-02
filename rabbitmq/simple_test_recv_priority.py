#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

#channel.queue_declare(queue='linxpq')
#channel.queue_bind(exchange='',queue='linxpq',routing_key='test')

print '文件 for test'
print ' [*] Waiting for messages. To exit press CTRL+C'

def callback(ch, method, properties, body):
    print type(body)
    print u" [UNICODE] Received %s" % body.decode("utf-8")

channel.basic_consume(callback,
                      queue='linxpq',
                      no_ack=False)

channel.start_consuming()

