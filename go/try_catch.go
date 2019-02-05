package main

import (
    "fmt"
    "errors"
)

func main() {
    err := testError()
    if err != nil {
        fmt.Println("main 函数得到错误类型:", err)
    }
    afterErrorfunc()
}

func testError() (err error) {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("[defer recover] testError() 遇到错误:", r)
            switch x := r.(type) {
            case string:
                err = errors.New(x)
            case error:
                err = x
            default:
                err = errors.New("")
            }
        }
    }()
    panic(" \"panic 错误\"") //panic 错误不会让defer 关键字定义的函数也停止运行,就是说defer 关键字声明的函数或者代码即使遇到错误也会执行。recover 会拦截错误，不会让错误往上扔，返回给调用者error（里面有错误的信息）类型 ，从而使goroutine 不挂掉。 
    fmt.Println("抛出一个错误后继续执行代码")
    return nil
}

func catch(err error) {
    if r := recover(); r != nil {
        fmt.Println("testError() 遇到错误:", r)
        switch x := r.(type) {
        case string:
            err = errors.New(x)
        case error:
            err = x
        default:
            err = errors.New("")
        }
    }
}

func afterErrorfunc() {
    fmt.Println("遇到错误之后 func ")
}


