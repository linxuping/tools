--lxp
function sleep(n)
   os.execute("sleep " .. n)
end


local newProductor

function productor()
     local i = 0
     while true do
          i = i + 1
          send(i)     -- 将生产的物品发送给消费者
     end
end

function consumer()
     while true do
          local i = receive()     -- 从生产者那里得到物品
          print("recv: ", i)
     end
end

function receive()
     local status, value = coroutine.resume(newProductor)
     sleep(1)
     return value
end

function send(x)
     print("yield here, send: ",x)
     coroutine.yield(x)     -- x表示需要发送的值，值返回以后，就挂起该协同程序
     sleep(1)
     print("yield here, send: ",x+100)
     coroutine.yield(x+100)     -- more senders one consumer
     sleep(1)
end

-- 启动程序
newProductor = coroutine.create(productor)   --after yield will change return value. 
consumer()



