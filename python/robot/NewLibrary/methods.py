# encoding=utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

class MyClass(object):
    def __init__(self):
        pass

    def printMsg(self,msg):
        import os
        os.system('mkdir /tmp/lxp.log')
        print "hello "+msg

    def writetbLog(self,title,quanter,integer,decimal,sale_count,img,code):
        title,quanter,integer,decimal,sale_count,img,code = title,str(quanter),str(integer),str(decimal),str(sale_count),img,code
        file = r'/tmp/tb.log'
        with open(file, 'w+') as f:
                f.write('"%s","%s","%s","%s","%s","%s","%s"\n'%(title,quanter,integer,decimal,sale_count,img,code))
        #import os
        #os.system('mkdir /tmp/lxp.log')
        #print "hello "+msg
