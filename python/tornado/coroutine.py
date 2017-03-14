import json
import tornado
import tornado.web
from tornado import gen
from tornado.options import define, options
define('port', default=9901, help='run on the given port', type = int)

@tornado.gen.coroutine
def count():
    print '-------sleep begin'
    gen.sleep(10)
    print '-------sleep finish'
    r = {}
    r['s'] = 1
    raise tornado.gen.Return(r)

class test1(tornado.web.RequestHandler):
    @tornado.gen.coroutine
    def get(self):
        print '------test1'
        r = yield count()
        s = 'return of test1\n'
        print 'count returns'
        self.write(s)
        self.write(json.dumps(r))

class test2(tornado.web.RequestHandler):
    @tornado.gen.coroutine
    def get(self):
        print 'do test2'
        self.write('test2 begin \n')
        self.write('test2 end')

application = tornado.web.Application([
    (r'/cor/test1', test1),
    (r'/cor/test2', test2)
])

if __name__ == '__main__':
    application.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

