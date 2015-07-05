/*
 * refer to: http://blog.csdn.net/zhangjingyangguang/article/details/5221691
 */
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <iostream>
#include <string.h>
using namespace std;

void test_run_file();
void test_run_fun();
void test_run_fun2();

int main()
{
	test_run_file();
	test_run_fun();
	test_run_fun2();

	return 0;
}

void test_run_fun()
{
    //Lua示例代码
    char *szLua_code =
        "r = string.gsub(c_Str, c_Mode, c_Tag) --宿主给的变量 "
        "u = string.upper(r)";
		printf("-- %s\n",szLua_code);
    //Lua的字符串模式
    char *szMode = "(%w+)%s*=%s*(%w+)";
    //要处理的字符串
    char *szStr = "key1 = value1 key2 = value2";
    //目标字符串模式
    char *szTag = "<%1>%2</%1>";
 
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
 
    //把一个数据送给Lua
    lua_pushstring(L, szMode);
    lua_setglobal(L, "c_Mode");
    lua_pushstring(L, szTag);
    lua_setglobal(L, "c_Tag");
    lua_pushstring(L, szStr);
    lua_setglobal(L, "c_Str");
 
    //执行
    bool err = luaL_loadbuffer(L, szLua_code, strlen(szLua_code), "demo") || lua_pcall(L, 0, 0, 0);
    if(err)
    {
        //如果错误，显示
        cerr << lua_tostring(L, -1);
        //弹出栈顶的这个错误信息
        lua_pop(L, 1);
    }
    else
    {
        //Lua执行后取得全局变量的值
        lua_getglobal(L, "r");
        cout << "r = " << lua_tostring(L,-1) << endl;
        lua_pop(L, 1);
        
        lua_getglobal(L, "u");
        cout << "u = " << lua_tostring(L,-1) << endl;    
        lua_pop(L, 1);
    }
    lua_close(L);
}

void test_run_fun2()
{
    //Lua示例代码，使用table
    char *szLua_code =
        "x = {} --用于存放结果的table "
        "x[1],x[2] = string.gsub(c.Str, c.Mode, c.Tag) --x[1]里是结果，x[2]里是替换次数 "
        "x.u = string.upper(x[1])";
    //Lua的字符串模式
    char *szMode = "(%w+)%s*=%s*(%w+)";
    //要处理的字符串
    char *szStr = "key1 = value1 key2 = value2";
    //目标字符串模式
    char *szTag = "<%1>%2</%1>";
 
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
 
    //把一个tabele送给Lua
    lua_newtable(L);    //新建一个table并压入栈顶
    lua_pushstring(L, "Mode");// key
    lua_pushstring(L, szMode);// value
    //设置newtable[Mode]=szMode
    //由于上面两次压栈，现在table元素排在栈顶往下数第三的位置
    lua_settable(L, -3);
    //lua_settable会自己弹出上面压入的key和value
 
    lua_pushstring(L, "Tag");// key
    lua_pushstring(L, szTag);// value
    lua_settable(L, -3);    //设置newtable[Tag]=szTag
 
    lua_pushstring(L, "Str");// key lua_pushstring(L, szStr);// value
    lua_settable(L, -3);    //设置newtable[Str]=szStr
 
    lua_setglobal(L,"c"); //将栈顶元素（newtable）置为Lua中的全局变量c
 
    //执行
    bool err = luaL_loadbuffer(L, szLua_code, strlen(szLua_code),
                "demo") || lua_pcall(L, 0, 0, 0);
    if(err)
    {
        //如果错误，显示
        cerr << lua_tostring(L, -1);
        //弹出栈顶的这个错误信息
        lua_pop(L, 1);
    }
    else
    {
        //Lua执行后取得全局变量的值
        lua_getglobal(L, "x");
 
        //这个x应该是个table
        if(lua_istable(L,-1))
        {
            //取得x.u,即x["u"]
            lua_pushstring(L,"u");    //key
            //由于这次压栈，x处于栈顶第二位置
            lua_gettable(L,-2);
            //lua_gettable会弹出上面压入的key，然后把对应的value压入
            //取得数据，然后从栈中弹出这个value
            cout << "x.u = " << lua_tostring(L,-1) << endl;
            lua_pop(L, 1);
            
            //取得x[1]和x[2]
            for(int i=1; i<=2; i++)
            {
                //除了key是数字外，与上面的没什么区别
                lua_pushnumber(L,i);
                lua_gettable(L,-2);
                cout << "x[" << i <<"] = " << lua_tostring(L,-1) << endl;
                lua_pop(L, 1);
            }
        }
 
        //弹出栈顶的x
        lua_pop(L, 1);
    }
    lua_close(L);
}


void test_run_file(){
	lua_State *lua = luaL_newstate();
	luaopen_base(lua);
	if (lua){
		printf("Run test.lua:  %d \n",luaL_dofile(lua, "object.lua"));
		//lua_pcall(lua, 0, LUA_MULTRET, 0); 
	}
	lua_close(lua);
}

