package test

import (
    "fmt"
    "time"
)

func fibonacci(c, quit chan int) {
    x, y := 1, 1
    for {
        select {
            case c <- x:            //send to c
                x, y = y, x + y
            case <-quit:            //v := <-ch  // 从ch中接收数据，并赋值给v
                fmt.Println("quit")
                return
            default:
                fmt.Println("default and blocking.")
        }
        time.Sleep(time.Second/2)
    }
}

func Test2ChanAndGo() {
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

func TestChan() {
    c := make(chan int) 
	fmt.Println("TestChan.") 
    //c := make(chan int, 1) 
    c <- 1
	fmt.Println("step 1.")   //block ?
    c <- 2
	fmt.Println("end.") //block ?
}

func TestSelectChan() {
    c := make(chan int, 1) 
	fmt.Println("TestChan.") 
    for {
        select {
            case c <- 1:             
                fmt.Println("c <- 1.")
            default:
                fmt.Println("default and blocking.")
        }
        time.Sleep(time.Second)
    }
	fmt.Println("end.") 
}


