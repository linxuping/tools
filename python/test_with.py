# encoding=utf-8
class Test(object):  
    def __init__(self,name,flag):  
        self.filename = name  
        self.flag = flag  
      
    def __enter__(self):  
        ''''' 
        @summary: 使用with语句是调用，会话管理器在代码块开始前调用，返回值与as后的参数绑定 
        '''  
        print "__enter__:Open %s"%self.filename  
        self.f = open(self.filename,self.flag)  
        return self.f  
          
    def __exit__(self,Type, value, traceback):  
        ''''' 
        @summary: 会话管理器在代码块执行完成好后调用（不同于__del__）(必须是4个参数) 
        '''  
        print "__exit__:Close %s"%self.filename,Type,value,traceback
        self.f.close()  
          
    def __del__(self):  
        print "__del__"  
          
if __name__ == "__main__":  
    print "START."  
    with Test('test_python.py','r+') as f:  
        #content = f.read()  
        print f  
    print "END."  
