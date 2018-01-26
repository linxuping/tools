
class Test(object): #不包含object setter会无效
	attr = 1
	'''
	@property
	def attr(self):
		return self.attr
	@attr.setter
	def attr(self,value):
		self.attr = value
	'''

	@property
	def attr2(self):
		print 'attr2 getter'
		return self.attr
	@attr2.setter
	def attr2(self,value):
		print 'attr2 setter'
		self.attr = value


t = Test()
#print t.attr #RuntimeError: maximum recursion depth exceeded
print t.attr2
t.attr2 = 2
#print t.attr2

