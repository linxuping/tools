#encoding=utf-8
'''
 simple framework.
'''

def _init():
	print "\ninit ...\n"

def _exit():
	print "\nend ...\n"

def wrapper(fun):
	def wrapped(arg, *args, **kwargs):
		_init()
		fun(arg, args, kwargs)
		_exit()
	return wrapped


@wrapper
def my_processor(arg, args, kwargs):
#def my_process(arg, *args, **kwargs):
	print "arg: ",arg
	print "args: ",args
	print "kwargs: ",kwargs

#do
my_processor(100, "args_1", "args_2", key1=11, key2=22)
#while.

'''带参
'''
def wrapper0(dbtype):
	def wrapped1(func):
		def wrapped2(*args):
			func(dbtype, *args)
		return wrapped2
	return wrapped1

@wrapper0("main")
def my_processor2(dbtype,x,y,z,u,v,w=None):
	print dbtype, x,y,z,u,v

my_processor2(1,2,3,'a','b')






