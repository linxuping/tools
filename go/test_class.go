package main

import "fmt"

//基类？？？
type IAnimal interface {
    Speak() string
}

type Cat struct{}
func (c Cat) Speak() string {
    return "cat speak"
}

type Dog struct{}
//func (d *Dog) Speak() string { //cannot use Dog literal (type Dog) as type IAnimal in array or slice literal: Dog does not implement IAnimal (Speak method has pointer receiver)
//  细节：  *Dog对应下文：animals := []IAnimal{Cat{}, &Dog{}}
func (d Dog) Speak() string {
    return "dog speak"
}



func main() {
    animals := []IAnimal{Cat{}, Dog{}}
    for _, animal := range animals {
        fmt.Println("animal item: ", animal.Speak())
    }

    names := []string{"stanley", "david", "oscar"}
    for i,v := range names {
        fmt.Println("item: ", i, v)
    }
    vals := make([]interface{}, len(names))
    for i, v := range names {
        fmt.Println(i,v)
        vals[i] = v
    }

    //测试接口嵌入
    fmt.Println("接口继承与组合：https://www.jianshu.com/p/150523db21a9")
    a := Ant{}
    b := Beef{ &a }
    fmt.Println( b.Speak() )
    b.IAnimal = &a
    fmt.Println( b.Speak() )
}

type Ant struct{}
func (a *Ant) Speak() string {
    return "ant speak"
}

type Beef struct{
    IAnimal
}
func (b *Beef) Speak() string {
    return "beef speak"
}


