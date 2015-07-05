-- g++ mytestlib.cpp -llua -shared -fPIC -o mytestlib.so
require "mytestlib"  --指定包名称

--在调用时，必须是package.function
print(mytestlib.add(1.0,2.0))
print(mytestlib.sub(20.1,19))
