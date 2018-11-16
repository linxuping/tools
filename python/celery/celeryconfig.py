#encoding=utf-8
from kombu import Exchange, Queue
from datetime import timedelta
#from routers import MyRouter

#BROKER_URL = 'amqp://'
#CELERY_RESULT_BACKEND = 'amqp://'
BROKER_URL = 'redis://localhost:6379/0'
CELERY_RESULT_BACKEND = 'redis://localhost:6379/1'

CELERY_TASK_SERIALIZER = 'json'
CELERY_RESULT_SERIALIZER = 'json'
CELERY_ACCEPT_CONTENT=['json']
CELERY_TIMEZONE = 'Europe/Oslo'
CELERY_ENABLE_UTC = True

# 定义一个默认交换机 和 一个媒体交换机
default_exchange = Exchange('dedfault', type='direct')
media_exchange = Exchange('media', type='topic')

# 创建三个队列，一个是默认队列，一个是video、一个image
CELERY_QUEUES = (
    Queue('default', default_exchange, routing_key='default',  consumer_arguments={'x-priority': 3}),
    Queue('test2', media_exchange, routing_key='media.*', consumer_arguments={'x-priority': 4}),
    Queue('test3', media_exchange, routing_key='media.*', consumer_arguments={'x-priority': 5}),
)

CELERY_DEFAULT_QUEUE = 'default'
CELERY_DEFAULT_EXCHANGE = 'default'
CELERY_DEFAULT_ROUTING_KEY = 'default'


CELERY_ROUTES = ({'tasks.sendmail': {
                        'queue': 'test',
                        'routing_key': 'media.test'
                 }},
                 {'tasks.sendqq': {
                        'routing_key': 'media.test1'
                 }},
                 {'tasks.sendwx': {
                        'routing_key': 'media.test1'
                 }})


CELERY_ANNOTATIONS = {
    'tasks.sendmail': {'rate_limit': '10/m'}
}

from celery.schedules import crontab
CELERYBEAT_SCHEDULE = {
    'taskA_schedule' : {
        'task':'tasks.sendqq',
        'schedule': 5,#crontab(hour=15, minute=26),
        'args':(5,6)
    }
}

#CELERYD_MAX_TASKS_PER_CHILD = 1
#CELERY_DISABLE_RATE_LIMITS = True #http://www.voidcn.com/article/p-tchgbnfc-mn.html

# 在出现worker接受到的message出现没有注册的错误时，使用下面一句能解决
CELERY_IMPORTS = ("tasks",)

