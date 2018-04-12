package test

import (
    "fmt"
    "time"
)

func fibonacci(c, quit chan int) {
    x, y := 1, 1
    for {
        select {
        case c <- x: //send to c
            x, y = y, x + y
        case <-quit: //v := <-ch  // 从ch中接收数据，并赋值给v
            fmt.Println("quit")
            return
        default:
            fmt.Println("default and blocking.")
        }
        time.Sleep(time.Second/2)
    }
}

func TestChan() {
    c := make(chan int)
    quit := make(chan int)
    go func() {
        for i := 0; i < 10; i++ {
            time.Sleep(2*time.Second)
            fmt.Println(<-c)  //就绪！！！
        }
        quit <- 0
    }()
    fibonacci(c, quit)
}
