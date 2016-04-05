print '+---- ---- --------- next test ---------- ---- ----+'
def yield_read_file():
	BLOCK_SIZE = 8
	def read_file():
		with open('result', 'rb') as f:
			while True:
				block = f.read(BLOCK_SIZE)
				if block:
					yield block
					#print block
				else:
					return
	ret=read_file() 
	print type(read_file)
	print type(read_file())
	import types
	print isinstance(read_file, types.GeneratorType)
	print isinstance(read_file(), types.GeneratorType)
	print ret.next()
	print ret.next()
yield_read_file()

print '+---- ---- --------- next test ---------- ---- ----+'
def yield_tree_fun_test():
    node = 1
    parent = 0
    def print_node():
        for i in range(2): 
            yield node
    val = print_node()
    print 'node: ',val.next()
    print 'parent: ',parent
    node = 11
    print 'node: ',val.next() #lazy evaluation
yield_tree_fun_test()

print '+---- ---- --------- next test ---------- ---- ----+'
def test_stackless():
				import stackless
				ping_channel = stackless.channel()
				pong_channel = stackless.channel()

				def ping():
						while ping_channel.receive(): #stock here
								print "PING"
								pong_channel.send("from ping")

				def pong():
						while pong_channel.receive():
								print "PONG"
								ping_channel.send("from pong")

				stackless.tasklet(ping)()
				stackless.tasklet(pong)()
				ping_channel.send("start ")
				pong_channel.send("start 2")
test_stackless()

print '+---- ---- --------- next test ---------- ---- ----+'
