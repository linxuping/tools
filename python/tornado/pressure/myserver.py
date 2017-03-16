import logging
import tornado.httpserver
import tornado.ioloop
import tornado.web
import time

from tornado.httpclient import AsyncHTTPClient
count=0
class MainHandler(tornado.web.RequestHandler):
    @tornado.web.asynchronous
    def get(self):
        global count
        count += 1
        print count
        http = tornado.httpclient.AsyncHTTPClient()
        http.fetch("http://localhost:9900/", callback = self._test_callback)
        #self.write("Hello to the Tornado world! ")
        #Flushes the current output buffer to the network.
        #self.flush()

    #_test_callback is a callback function used for the processing of the response from the async request
    def _test_callback(self, response):
        print "finish."
        self.write(response.body)
        #refer the offical document, we are responsible for the invocation of the finish function in the async case.
        self.finish()

settings = { 
    "debug": True,
}


class MainHandler2(tornado.web.RequestHandler):
    def get(self):
        http = tornado.httpclient.HTTPClient()
        print "/test2",http.fetch("http://localhost:9900/").buffer.getvalue()
        http.close()

settings = { 
    "debug": True,
}




application = tornado.web.Application([
    (r"/test", MainHandler),
    (r"/test2", MainHandler2),
], **settings)

if __name__ == "__main__":

    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(9901)
    tornado.ioloop.IOLoop.instance().start()

