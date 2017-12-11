#encoding=utf-8
from __future__ import print_function

from twisted.internet import reactor
from twisted.web.client import Agent, HTTPConnectionPool
from twisted.web.http_headers import Headers

pool = HTTPConnectionPool(reactor, persistent=True)
pool.maxPersistentPerHost = 1 #自动重连

agent = Agent(reactor, pool)
#agent = Agent(reactor)

d = agent.request(
    b'GET',
    b'http://126.com/',
    Headers({'User-Agent': ['Twisted Web Client Example']}),
    None)

def cbResponse(ignored):
    print('Response received: '+str(ignored))
d.addCallback(cbResponse) #first call

def cbShutdown(ignored):
    print('cbShutdown.')
    reactor.stop()
#d.addBoth(cbShutdown) #second call
#d.addBoth(lambda ignored: reactor.stop())
d.addBoth(lambda ignored: (print('stop.'),reactor.stop()) )

reactor.run()
#https://www.cnblogs.com/tracylining/p/3353808.html 
