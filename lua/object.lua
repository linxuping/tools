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
	self.area = 2
	self.length = 3
	self.breadth = 4
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
	print("Derived:print_this do.")
end
d=Derived:new(nil, 100, 200)
d:print_this()


