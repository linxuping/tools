#doc: https://www.cnblogs.com/attitudeY/p/6789370.html
#新式类 广度优先
class A:
    def foo(self):
        print('called A.foo()')

class B(A):
    pass

class C(A):
    def foo(self):
        print super(C,self)
        print('called C.foo()')

class D(B, C): 
    pass

#-------------------------------#

class A2(object):
    def foo(self):
        print('called A.foo()')

class B2(A2):
    pass

class C2(A2):
    def foo(self):
        print super(C2,self)
        print('called C2.foo()')

class D2(B2, C2): 
    pass



if __name__ == '__main__':
    d = D() 
    d.foo()
    print "----------> class(object) ----------->"
    d2 = D2() 
    d2.foo()

