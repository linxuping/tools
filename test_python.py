
#test_loop_count() #cannot find here

def test_loop_count():
    lis=[1,2,3,4]*10000000
    #print len(lis) #0.280s
    for item in lis: #0.95s
        pass
    #so get len better than loop

class Test:
    def __init__(self):
        fun = getattr(self,"run_xx") 
        fun()
    def run_xx(self):
        print "i am Test::run()"

def test_class_fun_obj():
    tt = Test()
    fun = getattr(tt,"run_xx")
    fun()



#test_loop_count()
test_class_fun_obj()

