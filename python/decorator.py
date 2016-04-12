def deco(func):
    def _deco(a, b):
        print("before myadd() called.")
        if a == 0:
            return -9999
        ret = func(a, b)
        print("  after  myadd() called. result: %s" % ret)
        return ret
    return _deco
 
@deco
def myadd(a, b):
    print(" myadd(%s,%s) called." % (a, b))
    return a + b
 
#print myadd(1, 2) #myfun called.
print myadd(0, 2)  #myfun will not be called.  -9999


