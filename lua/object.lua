-- object
--test: this 
Rectangle = {area=0, length=0, breadth=0}
function Rectangle:print_this()
	print("this: ", self, self.__index)
end
print(Rectangle)
Rectangle:print_this()


--test new methods.  
function Rectangle:new (o, length, breadth)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	self.area = 111
	self.length = length
	self.breadth = breadth
	self.baseelem = 1000000001
	return o
end
function Rectangle:getArea()
	return self.area
end
obj=Rectangle:new(nil, 10, 20)
print(obj:getArea(), obj.length)


--test: derive method
Derived=Rectangle:new(nil, 10, 20)
function Derived:new (o, length,breadth)
	o = o or Rectangle:new(o,length,breadth)
	setmetatable(o, self)
	self.__index = self
	return o
end
function Derived:print_this()
	print("Derived:print_this doing ...")
end
--lua本身没有类功能，它的类功能是通过元表来实现的。类的函数调用通过obj:function方式。
d=Derived:new(nil, 100, 200)
d:print_this()
d.print_this(d) -- : and . are diff
print(d.baseelem) -- find parent's __index and check.


