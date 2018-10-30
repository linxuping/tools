import time
from kazoo.client import KazooClient
from kazoo.client import KazooState

zk = KazooClient('127.0.0.1:2181')
zk.start()

print zk.get('/zookeeper')
quota = zk.get('/zookeeper/quota')
#zk.create('/zookeeper/quota/xptest', 'hello')
print zk.get_children('/zookeeper/quota')


@zk.DataWatch('/zookeeper/quota/xptest')
def my_func(data, stat, event):
    print("Data is %s" % data)
    print("Version is %s" % stat.version)
    print("Event is %s" % event)
 
while True:
    time.sleep(10)

