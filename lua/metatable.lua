--meta table test
mytable = { k1=1 }
mymetatable = { k2=2 }
setmetatable(mytable,mymetatable)


_metatable = getmetatable(mytable)
print(_metatable.k1, _metatable.k2)

mytable = setmetatable({key1 = "value1"}, {
  __index = function(mytable, key)
    if key == "key2" then
      return "metatablevalue"
    else
      return mytable[key]
    end
  end
})
print(mytable.key1,mytable.key2)



mytable = setmetatable({key1 = "value1"}, { __index = { key2 = "metatablevalue" } })
print(mytable.key1,mytable.key2)



--在对新索引键（newkey）赋值时（mytable.newkey = "新值2"），会调用元方法，而不进行赋值。而如果对已存在的索引键（key1），则会进行赋值，而不调用元方法 __newindex
mymetatable = {}
mytable = setmetatable({key1 = "value1"}, { __newindex = mymetatable })
print(mytable.key1)
mytable.newkey = "新值2"
print(mytable.newkey,mymetatable.newkey)
mytable.key1 = "新值1"
print(mytable.key1,mymetatable.newkey1)



mytable = setmetatable({key1 = "value1"}, {
  __newindex = function(mytable, key, value)
		rawset(mytable, key, "\""..value.."\"")
  end
})
mytable.key1 = "new value"
mytable.key2 = 4
print(mytable.key1,mytable.key2)



mytable = setmetatable({ 10, 20, 30 }, {
  __tostring = function(mytable)
    sum = 0
    for k, v in pairs(mytable) do
		sum = sum + v
	end
    return "表所有元素的和为 " .. sum
  end
})
print(mytable)


