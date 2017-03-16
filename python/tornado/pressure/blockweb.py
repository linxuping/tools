import tornado.ioloop
import tornado.web
import time
class MainHandler(tornado.web.RequestHandler):
    def get(self):
        time.sleep(3)
        self.write("001")
        print "001 fin."
application = tornado.web.Application([
    (r"/", MainHandler),
])
if __name__ == "__main__":
    application.listen(9900)
    tornado.ioloop.IOLoop.instance().start()

