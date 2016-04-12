def deco(func):
    def _deco(a, b):
        print("before myfunc() called.")
        if a == 0:
            return 0
        ret = func(a, b)
        print("  after  myfunc() called. result: %s" % ret)
        return ret
    return _deco
 
@deco
def myfunc(a, b):
    print(" myfunc(%s,%s) called." % (a, b))
    return a + b
 
#myfunc(1, 2) #myfun called.
myfunc(0, 2)  #myfun will not be called.


