class MyClass(object):
    def __init__(self):
        pass
 
    def printMsg(self,msg):
        import os
        os.system('mkdir /tmp/lxp.log')
        print "hello "+msg

