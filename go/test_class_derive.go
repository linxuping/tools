package main

import (
    "fmt"
    "strconv"
    . "time"     //省略前缀的包名(https://wlcacc.iteye.com/blog/2427700)
    _ "net/http" //无法通过包名来调用包中的导出函数，而是只是为了简单的调用其init函数()。
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
    createTime  Time
    timeStamp  int
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

func GetNow() Time { //time.Time
    return Now()     //time.Now()
}

//多参数同类型、多返回值、return默认返回传参数
func GetReturnMulti(v1,v2 int) (var1,var2 string) {
    s1 := strconv.Itoa(v1)
    s2 := strconv.Itoa(v2)
    s2 = s2[ 0:len(s2)-2 ] //1999 -> 19
    var1,var2 = s1+s2+"_a\na1",s1+"_s_"+`_a\na2`
    return
}

func main() {
    var b Train
    //b.weight = 100
    //b.name = "train"
    b.Set(100, "train")
    b.createTime = GetNow()
    b.timeStamp = int(Now().Unix())
    b.lunzi = 2
    b.Run()
    fmt.Println(b)
    fmt.Printf("%s", &b)
    fmt.Println("[test] multi return func ---->")
    fmt.Println( GetReturnMulti(8,1999) )
}

