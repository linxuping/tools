
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

print '+--------- next test ----------+'

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
