#include <stdio.h>
#include <string.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
/*
//待Lua调用的C注册函数。
static int add2(lua_State* L)
{
    //检查栈中的参数是否合法，1表示Lua调用时的第一个参数(从左到右)，依此类推。
    //如果Lua代码在调用时传递的参数不为number，该函数将报错并终止程序的执行。
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    //将函数的结果压入栈中。如果有多个返回值，可以在这里多次压入栈中。
    lua_pushnumber(L,op1 + op2);
    //返回值用于提示该C函数的返回值数量，即压入栈中的返回值数量。
    return 1;
}

//另一个待Lua调用的C注册函数。
static int sub2(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

const char* testfunc = "print(add2(1.0,2.0)) print(sub2(20.1,19))";

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //将指定的函数注册为Lua的全局函数变量，其中第一个字符串参数为Lua代码
    //在调用C函数时使用的全局函数名，第二个参数为实际C函数的指针。
    lua_register(L, "add2", add2);
    lua_register(L, "sub2", sub2);
    //在注册完所有的C函数之后，即可在Lua的代码块中使用这些已经注册的C函数了。
    if (luaL_dostring(L,testfunc))
        printf("Failed to invoke.\n");
    lua_close(L);
    return 0;
}
*/



//待注册的C函数，该函数的声明形式在上面的例子中已经给出。
//需要说明的是，该函数必须以C的形式被导出，因此extern "C"是必须的。
//函数代码和上例相同，这里不再赘述。
extern "C" int add(lua_State* L) 
{
		printf("add into ... ...\n");
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 + op2);
    return 1;
}

extern "C" int sub(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

//luaL_Reg结构体的第一个字段为字符串，在注册时用于通知Lua该函数的名字。
//第一个字段为C函数指针。
//结构体数组中的最后一个元素的两个字段均为NULL，用于提示Lua注册函数已经到达数组的末尾。
static luaL_Reg mylibs[] = { 
    {"add", add},
    {"sub", sub},
    {NULL, NULL} 
}; 

//该C库的唯一入口函数。其函数签名等同于上面的注册函数。见如下几点说明：
//1. 我们可以将该函数简单的理解为模块的工厂函数。
//2. 其函数名必须为luaopen_xxx，其中xxx表示library名称。Lua代码require "xxx"需要与之对应。
//3. 在luaL_register的调用中，其第一个字符串参数为模块名"xxx"，第二个参数为待注册函数的数组。
//4. 需要强调的是，所有需要用到"xxx"的代码，不论C还是Lua，都必须保持一致，这是Lua的约定，
//   否则将无法调用。
extern "C"  // __declspec(dllexport)
int luaopen_mytestlib(lua_State* L) 
{
    const char* libName = "mytestlib";
    //luaL_register(L,libName,mylibs);
    lua_register(L,"add",add);
    lua_register(L,"sub",sub);
    return 0;
}

