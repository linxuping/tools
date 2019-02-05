package main

import "fmt"

type Animal interface {
    Speak() string
}

type Cat struct{}
func (c Cat) Speak() string {
    return "cat"
}

type Dog struct{}
//func (d *Dog) Speak() string { //cannot use Dog literal (type Dog) as type Animal in array or slice literal: Dog does not implement Animal (Speak method has pointer receiver)
func (d Dog) Speak() string {
    return "dog"
}

func Test(params interface{}) {
    fmt.Println(params)
}

func PrintAll_Strings(vals []string) {
    for _, val := range vals {
        fmt.Println(val)
    }
}
func PrintAll_Interfaces(vals []interface{}) {
    for _, val := range vals {
        fmt.Println(val)
    }
}

func main() {
    animals := []Animal{Cat{}, Dog{}}
    for _, animal := range animals {
        fmt.Println(animal.Speak())
    }

    Test(123)
    Test(true)
    Test("print Strings test start: ")

    names := []string{"stanley", "david", "oscar"}
    PrintAll_Strings(names)
    Test("pirnt Interfaces test start: ")
    vals := make([]interface{}, len(names))
    for i, v := range names {
        fmt.Println(i,v)
        vals[i] = v
    }
    PrintAll_Interfaces(vals)
}
