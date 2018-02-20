package test
// go语言如何转化函数类型为字符串类型值

import (
    "fmt"
)

func Testfunc() {
    add(test1, "Hi", "You", "Are", 1)
    add(test2, "Hi", "You", "Are", 2)
    add(test3, "Hi", "You", "Are", 3)

    add(test1, "test1", "Hi", "You", "Are", 1)
}

// 管理函数调用的入口
func add(name func(...interface{}), args ...interface{}) {
    // 问题: 我想在该处记录每一次添加进来的函数名称和参数列表, 请问应该如何转化函数类型为字符串类型?
    // 当前添加的函数, 参数列表
    fmt.Println(fmt.Sprintf("函数: %s, 参数: %s", "该处如何转化参数中的name函数类型为字符串函数名?", args))
    name(args)

    // 目前我自己的处理方法是, 将可变参数列表的第一个参数二次传入作为函数名, 显得比较笨, 应该有更好的方式
    // 比如上面测试用例的test1函数
    fmt.Println(fmt.Sprintf("函数: %s, 参数: %s", args[:1], args[1:]))
    name(args)
}

// 具体的函数1
func test1(args ...interface{}) {
    fmt.Println("test1...")
    fmt.Println(args)
}

// 具体的函数2
func test2(args ...interface{}) {
    fmt.Println("test2...")
    fmt.Println(args)
}

// 具体的函数3
func test3(args ...interface{}) {
    fmt.Println("test3...")
    fmt.Println(args)
}
