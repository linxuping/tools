#encoding: utf-8
'''
@doc http://python.jobbole.com/87294/
__metaclass__
__new__
__init__
'''
class Singleton(type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        print "Singleton __call__"
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]

    def __new__(cls, *args, **kwargs):
        print "Singleton __new__"
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__new__(cls, *args, **kwargs)
        return cls._instances[cls]

#Python2
class MyClass(object):
    __metaclass__ = Singleton
 
def test_equal(c1, c2):
	print id(c1), id(c2), c1==c2, c1 is c2 

class Normal():
	m = 2

'''
__new__出实例obj，然后多次__call__均返回obj
'''
test_equal(MyClass(),MyClass())
test_equal(Normal(),Normal())
print MyClass().__class__

print '''
hello #word
'''

# ---------------->>>
# Python3
# class MyClass(metaclass=Singleton):
#    pass


