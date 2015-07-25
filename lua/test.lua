--comment one
--[[
comment 
multiple
--]]
print("lua version: ".._VERSION)

--Lua中有8个基本类型分别为：nil、boolean、number、string、userdata、function、thread和table
print(b, type(b))
b=nil
print(b, type(b))
b=10
print(b, type(b))
b=true
print(b, type(b)) 
b=[[
<html>hello</html>
]]
print(b, type(b), "length: ", #b) 

tab1 = { k1="var1", k2=1234, "val3" }
print(tab1, type(tab1)) 
tab1.k1 = "var1111"
tab1.k3 = "var3333"
for k,v in pairs(tab1) do
	print(k .. " - " .. v)
end
print("operator.", tab1.k1, tab1.k2) --, tab1.1

tab2 = { "apple","pear","grape" }
for k,v in pairs(tab2) do
	print(k)
end

if false or type(false) or type(nil) then --type(false) is boolen and means false ?
	print("into false.")
else
	print("into true.")
end

print("4"+2)
--print("error"+2)
print(44 .. 2)
print('44' .. "55" .. 2)

function check(n)
	if n == 0 then
		return false
	else
		return true
	end
end
print(check, check(2), check(0), type(check))

x, y = y,x,z --from right to left: y=x ; x=y
function ret1()
	return 101,102
end
a,b = ret1()
print(a,b)

a=15
while(a>10) do
	print(a) -- no a-- --a 
	a = a - 1
end

a=10
print(a^3)

print( "string.gsub: ", string.gsub("aaaaaa","a","b",3) )
a = string.find("aaa abc abcd","abc",3)
print( a,type(a) )
print( string.format("format:%d ", 8) )
print( string.char(97,98,99) )
print( string.byte("ABCD", 4) )
print( "ascii, A and a :", string.byte("ABCDZ"), string.byte("abcdz") )
print( "ascii, Z and z :", string.byte("ABCDZ",-1), string.byte("abcdz",-1) )
print( "string.len", string.len("ABCDefg") )
print( "find: ", string.find("abcdefg", "cde") )
print( "find: ", string.find("abcdefg", "cdm") )
date = 2; month = 1; year = 2014
print( string.format("日期格式化 %02d/%02d/%03d", date, month, year))
print( "string.rep ", string.rep("xyz",3) )

arr = {3,4,5}
for i=0, 2 do
	print(arr[i], arr.i) --Lua 索引值是以 1 为起始  no  arr.i
end
for i=-2, 2 do
	arr[i] = i*2
end
for i=-2, 2 do
	print(arr[i])
end

function square(iteratorMaxCount,currentNumber)
   print("args: ",iteratorMaxCount,currentNumber)
   if currentNumber<iteratorMaxCount
   then
      currentNumber = currentNumber+1
   return currentNumber, currentNumber*currentNumber
   end
end

for i,n in square,3,0
do
   print(i,n)
end

fruits = {"banana","orange","apple"}
print("连接后的字符串 ",table.concat(fruits))
print("连接后的字符串 ",table.concat(fruits,", "))
print("连接后的字符串 ",table.concat(fruits,", ", 2,3))
table.insert(fruits,2,"grapes")
print("索引为 2 的元素为 ",fruits[2])
print("最后一个元素为 ",fruits[4])
table.remove(fruits)
print("移除后最后一个元素为 ",fruits[4])
table.sort(fruits)

print("\n+-------------- table len ---------------+")
tbl = {[1] = "a", [2] = "b", [3] = "c", [26] = "z", ["fun"]="x"}
for k,v in pairs(tbl) do
	print("tbl item(pairs): ", k,v)
end
print("tbl 长度 ????  ", #tbl) -- 因为26和之前的数字不连续, 所以不算在数组部分内 !!!

for k,v in ipairs(tbl) do
	print("tbl item(ipairs, if nil will break): ", k,v)
end
--print("tbl 长度   ", table.getn(tbl)) 
--a = { [f(1)] = g; "x", "y"; x = 1, f(x), [30] = 23; 45 }


print("\n+-------------- string ---------------+") --http://www.cnblogs.com/whiteyun/archive/2009/08/10/1543139.html
tbl = {"alpha", "beta", "gamma"}
print(table.concat(tbl, ":"))
print(table.concat(tbl, nil, 1, 2))
print(table.concat(tbl, "\n", 2, 3))
table.insert(tbl, 3, "zeta")
print(table.concat(tbl, ", ") )
table.sort(tbl)
--table.sort(guild, sortLevelNameAsc)

print("\n+--------------- table ---------------+")
temp = 2
tab = {[temp] = 1, 11}
temp = 1
print(tab[temp])

print("\n+-------------- metatable ---------------+")
mytable = setmetatable({key1 = "value1"}, { 
	__index = { key1="key1", key2="metatablevalue" } ,
	__tostring = function(mytable)
		for k,v in pairs(mytable) do
			print("item: ",k,v)
		end
		return "元素 len: " .. #mytable
	end
} 
)
print(mytable.key1,mytable.key2)
print(mytable, #mytable)

print("\n+-------------- module ---------------+")
local m = require("mymodule")
print(m.constant)
opts = {ip="localhost"}
ret = m.init( opts )
print("init: ", ret, ret.key1, ret.ip)

print("\n+-------------- module2 ---------------+")
--local m = require("mymodule2")
--opts = { buf = "my.buf" }
--sender = gen_sender(opts)
--print("sender: ", sender, sender.buf)
--sender:send()

print("\n+-------------- io ---------------+")
io.input("mymodule.lua")  
t=io.read(6)  --io.read("*line")  --io.read("*all")  
io.write(t, '\n')  ------输出整个 hello.lua 文件的内容到 stdin


