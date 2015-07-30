/*
 * https://www.chenlq.net/books/c-mate/learn-the-c-language-how-to-write-a-more-advanced-calculator-how-to-calculate-the-value-of-a-string-representation-formula-the-use-of-stack-stack-according-to-the-operator-precedence-method.html
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <cctype>
#include <stack>  // 栈容器
 
using namespace std;
 
// 返回两个操作符之间的优先级关系
char cmp(char a, char b)     
{
    switch(a)
    {
        case '#': // '#'优先级最低
            return ('#'==b)?'=':'<';
        break;
        case '+':
        case '-': // '+''-'的优先级小于'*''/''('
        {
            if('*'==b || '/'==b || '('==b)
                return '<';
            else
                return '>';
        }
        break;
        case '*':
        case '/': // '*''/'的优先级小于'('而大于其他
        {
            return ('('==b)?'<':'>';              
        }
        break;
        case '(': // '('的优先级等于')'
            return (')'==b)?'=':'<';
        break;
        default: // 不支持的操作符，抛出异常
            throw "error:unkown operator";
    }
}
 
// 用操作符对两个操作数进行操作，返回结果
int calc(int a, int b, char op) 
{
    switch(op)
    {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            if(0 == b) // 特殊处理除数为0
                throw "error: the divisor shoud not be negtive.";
            else 
                return a/b;
        default:
            throw "error: unknown operator.";
    }
}
 
 
// 判断当前字符是否是操作符
bool isoptr(char c)               
{
    // 合法的操作符列表
    static string optrs("+-*/()#");
    // 如果在列表中无法找到
    if(optrs.find(c) == string::npos)
    {
        if(isdigit(c))
            return false;    //不是算符
        else // 不支持的操作符
            throw "error: unknown char.";
    }
 
    return true; // 是操作符
}
 
// 求计算式e的值
int eval(string e)  
{
    e += "#"; // 添加一个#表示表达式结束
    stack<int> opnd;        // 操作数栈
    stack<char> optr;       // 操作符栈
    optr.push('#'); // 在操作符栈添加'#'表示开始
    int i = 0; // 计算式的起始扫描位置
    int    num = 0; // 从表达式中提取的数字
 
    // 这个字符解析计算式
    // 直到表达式没有遇到结束符'#'
    // 或者操作符栈中还有操作符
    while(e[i]!='#' || optr.top()!='#')
    {   
				//printf("e[i]:%c \n",e[i]);
        // 判断当前字符是否是操作符
        if(!isoptr(e[i]))
        {   
            // 不是操作符,则是操作数
            // 利用循环从计算式中提取数字
            num = 0;
            // 逐个字符相后遍历，直到遇到操作符为止
            while(!isoptr(e[i]))
            {     
                num *= 10; // 将已经提取的数字向前移动一位
                num += e[i] - '0'; // 加上当前数字， 
                ++i;   
            }
            // 将操作数压入操作数栈
						printf("push: %d \n",num);
            opnd.push(num);
        }
        else // 如果当前字符是操作符
        {
            // 比较当前操作符与操作符栈顶操作符的优先级
            // 根据优先级采取不同策略
            if(optr.empty())
            {
                throw "error: optr is empty";
            }
						printf("cmp:%c %C %c\n",optr.top(),cmp(optr.top(),e[i]),e[i]);
            switch(cmp(optr.top(),e[i]))
            {
                // 栈顶操作符优先级低,暂不计算，新操作符入栈
                // 比如在1+2中，操作符栈中最开始的#和+比较，
                // #小于+,所以不执行计算，+直接压入操作符栈
                case '<': // 小于
                    optr.push(e[i]);
                    ++i; // 解析下一个字符
                    break;
                // 优先级相等，说明')'遇到了'(',
                // 或者是'#'遇到了'#'，
                // 那么')'或'#'出栈，新符号不入栈  
                case '=':
                    optr.pop();
                    ++i;
                    break;
                // 栈顶运算符优先级高，暂停输入，计算
                // 比如，1+2#末尾的#，当他与此时栈顶+比较
                // +的优先级大于#，从操作数栈中取两个数1和2，
                // 同时取出操作符栈顶的+进行计算
                case '>': 
                    // 取出两个数计算结果
                    if(opnd.empty())  
                    {  
                        throw "error: opnd is empty.";  
                    }
                    // 从操作数栈中取第一个数
                    int a = opnd.top(); opnd.pop();
                    if(opnd.empty())  
                    {  
                        throw "error: opnd is empty."; 
                    }
                    // 取第二个数
                    int b = opnd.top(); opnd.pop();
										printf("pop: %d \n",b);
										printf("calc: %d %c %d = %d \n",b,optr.top(),a,calc(b, a, optr.top()));
                    
                    // 这里要注意a，b的顺序，a先出栈，也就是后入栈，说明是操作符
                    // 之后的操作数，所以这里应该是b op a
                    // 将计算结果压入操作数栈，作为新的操作数
                    opnd.push(calc(b, a, optr.top()));    //注意这里a和b的顺序
                    // 已经计算过的操作符出栈
                    optr.pop();
                    // 注意，这里没有进行++i，
                    // 而是直接再次对当前操作符进行处理
                    break;   
            }   
        }
    }
   
    // 返回最后留存在操作数栈中的计算结果 
    return opnd.top();
}
 
int main()
{
    string expr;    // 计算式
 
    while(true)
    {
        cout<<"please input the expression.  'end' for exit"<<endl;
        cin>>expr;
        
        if("end" == expr)
            break;
 
        try
        {
            int res = eval(expr);
            cout<<expr<<" = "<<res<<endl;
        }
        catch (const char* err)
        {
            cout<<err<<endl;
        }
    }
 
    return 0;
}

