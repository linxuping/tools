# -*- coding: utf-8 -*-
'''README
Python 2.7.6 (default, Jul 25 2014, 10:59:32)
Version('twisted', 10, 2, 0)
'''
from twisted.web import http, resource, server
#与“心跳”有关的配置项
#“心跳”间隔，正整数，单位为秒
state_agent_interval = 3 
#指定处理“心跳”的服务器
state_agent_service = "squid.ucfly.com:3128"
#与处理“心跳”的服务器的超时时间，单位为秒
state_agent_timeout = 3 
#对外服务端口，格式为[["ip1",port1],["ip2",port2]],
#ip如果为空字符串，则表示绑定机器上的所有接口上且调试端口失效
ucweb_service_port = [["", 9903]]


class clsAcceptor(object):
  #所有请求的父类
  def set_req_func(self, func_list):
    #设置接收到请求时调用的处理函数列表
    self.req_process_func_list = func_list
    print '>>> clsAcceptor(object) set_req_func'


class clsUcwebServer(clsAcceptor, resource.Resource):
  def __init__(self):
    resource.Resource.__init__(self)
  def render_GET(self, request):
    print '>>> clsUcwebServer(clsAcceptor, resource.Resource) render_GET '
    return "render_GET"
  def render_POST(self, request):
    #self.req_process_func_list[0](request) -> several worker threads work.
    print '>>> clsUcwebServer(clsAcceptor, resource.Resource) render_POST '
    return "render_POST"


class homeRes(resource.Resource):
  def render(self,request):
    return """
    <html>
    <head></head>
    <body style='background-color: #'>
    <h1>This is demo.</h1> <p style='background-color: white'>
    <a href='/color/'>Back</a>
    </p>
    </body>
    </html>
    """ 


class FHTTPChannel(http.HTTPChannel):
  def __init__(self):
    http.HTTPChannel.__init__(self)
  def connectionMade(self):
    self.setTimeout(self.timeOut)
    print ">>> FHTTPChannel(http.HTTPChannel)::connectionMade "
  def connectionLost(self, reason):
    print ">>> ",reason


class FRequest(server.Request):
  def __init__(self, *args, **kw):
    server.Request.__init__(self, *args, **kw)
    self.arrived_time = None
    self.had_req_dump = False
    self.project_type = 0
'''
  def process(self):
    #self.setHeader("Content-Type",'text/html')
    print ">>> FRequest(server.Request) "
    self.write("<h1>Not Found</h1>Sorry, no such page.")
    self.finish()
'''


class FSite(server.Site):
  requestFactory = FRequest
  def __init__(self, resource, logPath=None, timeout=60*60*12):
    server.Site.__init__(self, resource, logPath, timeout)
    self.protocol = FHTTPChannel
    self.keep_client_connections = []


def ucweb_req_process(http_request):
  print '>>> fun: ucweb_req_process(http_request)'
  pass

def start_state_agent():
   #定时向指定服务器发送“心跳”信息
   global state_agent_interval
   if state_agent_interval <= 0:
     state_agent_interval = 1 
   try:
     import httplib,socket
     connection = httplib.HTTPConnection(state_agent_service)
     connection.connect()
     connection.sock.settimeout(int(state_agent_timeout))
     state_data = {}
     state_data["ip"] = str(socket.gethostbyname_ex("localhost.ucfly.com")[2][0])
     print "+ ",ucweb_service_port
     state_data["port"] = str(ucweb_service_port[0][1])
     body = "`".join(["=".join(s1) for s1 in state_data.items()])
     connection.request("POST", "/", body, {"User-Agnet": "StateAgent"})
     connection.close()
   except:
     import sys
     import traceback
     print sys.exc_info(), traceback.format_exc()
     #state_agent_error_count += 1
     #if 10 < state_agent_error_count:
     #  state_agent_error_count = 0 
       #log.error("failed to report state data, because of (%s)" % e)
   reactor.callLater(int(state_agent_interval), start_state_agent)


from twisted.internet import reactor
ucweb_accept = clsUcwebServer() #Resource
ucweb_accept.set_req_func((ucweb_req_process,)) #ucweb_req_processor.put_req(ucweb_req) ucweb_req_processor=clsUcwebReqProcessor() class clsUcwebReqProcessor(clsProcessor) clsProcessor->workerthreads
ucweb_accept.putChild('',homeRes())
for ip, port in ucweb_service_port: #
    site = FSite(ucweb_accept, timeout=120)
    ucweb_service_port_obj = reactor.listenTCP(port, site, interface=ip)
reactor.callLater(int(state_agent_interval), start_state_agent)
#reactor.callLater方法用于设置定时事件：
#reactor.callLater函数包含两个必须参数，等待的秒数，和需要调用的函数
reactor.run(installSignalHandlers=0)

'''DESC
从twisted.web包中引入了几个类：resource.Resource、static.File、server.Site。每个resource.Resource对象做两件事。首先，定义请求的资源如何处理。第二，定义请求子资源的Resource对象。

'''

