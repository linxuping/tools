#pip install celery\celery-with-redis
import time
from tasks import sendmail
r = sendmail.delay(dict(to='celery@python.org'))
print 'get ', r.get()
time.sleep(1)
print 'get ', r.get()
time.sleep(1)
print 'get ', r.get()
time.sleep(1)
print 'get ', r.get()
time.sleep(1)
print '--end--'

