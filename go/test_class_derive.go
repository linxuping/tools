package main

import (
    "fmt"
    "time"
)

/*
继承
一个结构体嵌到另一个结构体，称作组合
匿名和组合的区别
如果一个struct嵌套了另一个匿名结构体，那么这个结构可以直接访问匿名结构体的方法，从而实现继承
如果一个struct嵌套了另一个【有名】的结构体，那么这个模式叫做组合
如果一个struct嵌套了多个匿名结构体，那么这个结构可以直接访问多个匿名结构体的方法，从而实现多重继承
*/

type Car struct {
    weight int
    name   string
    createTime  time.Time
}

func (c *Car) Set(weight int, name string) {
    c.weight = weight;
    c.name = name;
}

func (p *Car) Run() {
    fmt.Println("running")
}

type Train struct {
    Car
    lunzi int
}

func (p *Train) String() string {
    str := fmt.Sprintf("String() name=[%s] weight=[%d]\n", p.name, p.weight)
    return str
}

func Now() time.Time {
    return time.Now()
}

func main() {
    var b Train
    //b.weight = 100
    //b.name = "train"
    b.Set(100, "train")
    b.createTime = Now() 
    b.lunzi = 2
    b.Run()
    fmt.Println(b)
    fmt.Printf("%s", &b)
}

