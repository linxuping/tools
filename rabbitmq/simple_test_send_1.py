#!/usr/bin/env python
'''Usage
RECV: ./examples/amqp_listen localhost 5672 amq.direct test python simple_test_send_1.py 
SEND: python simple_test_send_1.py 
'''
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

channel.queue_declare(queue='')

channel.basic_publish(exchange='amq.direct',
                      routing_key='test',
                      body='Hello World!')
print " [x] Sent 'Hello World!'"
connection.close()

