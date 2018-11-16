#pip install celery\celery-with-redis
import sys
import time
from tasks import *
print 'send'
#r = sendmail.delay(dict(to='celery@python.org'), None)
r = sendwx.delay('jim', 'hello')
print 'sended'
for i in range(0,10):
    try:
        print 'get ', r.get(timeout=1),r.ready(),r.traceback
    except:
        print sys.exc_info()
'''
r = sendmail.delay(dict(to='celery@python.org'))
for i in range(0,10):
    try:
        print 'get ', r.get(propagate=False),r.ready(),r.traceback
    except:
        print sys.exc_info()
'''

print '--end--'

