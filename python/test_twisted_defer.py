#encoding=utf-8
from twisted.web.client import getPage
from twisted.internet import reactor
import socket
socket.setdefaulttimeout(2)

# ---- getPage ----
def errorHandler(error):
    '''
    这是一个“errback”函数，被添加到Deferred，当出现错误事件是，Deferred将会调用它
    '''
    # 这么处理错误并不是很实际，我们只是把它打出来：
    print "An error has occurred: <%s>" % str(error)
    # 然后我们停止整个处理过程：
    #reactor.stop()

def successHandler(contents):
    '''
    这是一个“callback”函数，被添加到Deferred，Deferred会把页面内容作为参数调用它
    '''
    print 'success: ',len(contents)
    #reactor.stop()

def visit_url(url):
    # 我们请求一个不存在的页面，来演示错误链
    deferred = getPage(url)

    # 向Deferred添加callback，以处理页面内容
    deferred.addCallback(successHandler)

    # 向Deferred添加errback，以处理任何错误
    deferred.addErrback(errorHandler)
# ---- getPage END ----

# ---- threads.defer ----
from twisted.internet import threads
import time
def CostTimeWork(x):
    '''
    这是一个耗时的任务
    '''
    for i in xrange(3):
        print("cost time:%s\t%s" % (i,x))
        time.sleep(1)
    return x

def PrintData(res):
    '''
    回调函数，打印结果
    当耗时任务结束后，想要如何对结果进行处理，就要用到回调。
    我这里只是简单打印结果而已
    '''
    print res

def test_busy_cpu():
    #将耗时函数 放入另一个线程实行，返回一个deferred对象
    d = threads.deferToThread(CostTimeWork,"loop")
    #添加回调函数
    d.addCallback(PrintData)
# ---- threads.defer END ----


print 'test cpu block.'
test_busy_cpu()
print 'test net block.'
visit_url('http://test.wekuo.com/api/circle/xptest') #blocking
print 'test net error.'
visit_url('http://twistedmatrix.com/does-not-exist')
print 'test net success.'
visit_url('http://www.baidu.com/')

reactor.run()


#http://blog.sina.com.cn/s/blog_6262a50e0101o2tq.html
#getPage(url, method='POST', postdata=postdata, headers=headers)


