--LUA_PATH finding
--[[
 如果找过目标文件，则会调用 package.loadfile 来加载模块。否则，就会去找 C 程序库。
搜索的文件路径是从全局变量 package.cpath 获取，而这个变量则是通过环境变量 LUA_CPATH 来初始。
搜索的策略跟上面的一样，只不过现在换成搜索的是 so 或 dll 类型的文件。如果找得到，那么 require 就会通过 package.loadlib 来加载它。 
--]]

--module(...) --直接用文件名引用，而不必每次修改，缺点代价是，无法直接运行模块，必须引用，否则出现未给定值。
local mt = { __index = _M }
--opts = { sock=?, buf=? }
function gen_sender(opts)
	return setmetatable({buf="my.test"}, mt)
end

--sender obj
function send(self)
	print("inter send ... ...")
	print("send. ",self.buf)
end
--sender obj end

--for a,b in pairs(_G) do print(a,b) end

local class_mt = {
    -- to prevent use of casual module global variables
    __newindex = function (table, key, val)
      error('attempt to write to undeclared variable "' .. key .. '"')
    end
}

setmetatable(_M, class_mt)

