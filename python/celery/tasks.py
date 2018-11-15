# encoding=utf-8
import time
from celery import Celery

celery = Celery('tasks', broker='redis://localhost:6379/0', backend='redis://localhost:6379/1')
celery.config_from_object('celeryconfig')
'''
app.conf.CELERY_TASK_SERIALIZER = 'json'
celery.conf.update(
    CELERY_TASK_SERIALIZER='json',
    CELERY_ACCEPT_CONTENT=['json'],  # Ignore other content
    CELERY_RESULT_SERIALIZER='json',
    CELERY_TIMEZONE='Europe/Oslo',
    CELERY_ENABLE_UTC=True,
)
'''
@celery.task
def sendmail(mail, to):
    print('sending mail to %s...' % mail['to'])
    time.sleep(2)
    print('mail sent.')
    return 'mail sended'

@celery.task
def sendqq(user, text):
    print('sending qq to user...')
    time.sleep(2)
    print('qq sent.')
    return 'qq sended'

@celery.task
def sendwx(user, text):
    print('sending wx to user...')
    time.sleep(2)
    print('wx sent.')
    return 'wx sended'


#celery -A tasks worker --loglevel=info
#celery worker --loglevel=info -Q test

'''
https://www.jianshu.com/p/1840035cb510
schedule需要加-B参数才能执行，然后还要对应上队列处理 test2
celery worker --loglevel=info -Q test2 -B
'''



