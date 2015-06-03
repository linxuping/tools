#!/usr/bin/env python
'''Usage
python receive_logs_topic.py linxpq1
python receive_logs_topic.py linxpq2
'''
import pika
import sys

queuename = sys.argv[1]

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

channel.exchange_declare(exchange='topic_logs',
                         type='topic')
'''
channel.queue_declare(queue='linxpq1', durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
channel.queue_declare(queue='linxpq2', durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
channel.queue_bind(exchange='topic_logs', queue='linxp1', routing_key="zb.*")
channel.queue_bind(exchange='topic_logs', queue='linxp2', routing_key="zb")
'''
result = channel.queue_declare(queue=queuename, durable=True, exclusive=False, auto_delete=False, arguments={"x-max-priority":10})
queue_name = result.method.queue

print ' [*] Waiting for logs. To exit press CTRL+C'

import time
def callback(ch, method, properties, body):
    print ch, method, properties, body
    print " [x] %r:%r" % (method.routing_key, body,)
    time.sleep(1)

channel.basic_consume(callback,
                      queue=queue_name,
                      no_ack=True)

channel.start_consuming()

