package main

import (
    "fmt"
    "database/sql"
    "os/exec"
    _ "github.com/go-sql-driver/mysql"
    //"github.com/Unknwon/goconfig"
)

type DbWorker struct {
    //mysql data source name
    Dsn string
}

type TBase struct {
    begin bool
}
type Tester struct {
    TBase
    is_tester bool
}

func (t *Tester) get_table_count() (int) {
    t.begin = true //t *Tester才生效
    defer error_catch()
    dbw := DbWorker{
        Dsn: "cootekime:CooTek01@tcp(localhost:3306)/ime_matrix",
    }
    db, err := sql.Open("mysql", dbw.Dsn)
    if err != nil {
        panic(err)
        return -1
    }
    rows, err := db.Query(`SELECT count(1) From matrix_sevenfit_post`)
    var count int = -1
    for rows.Next() {
        rows.Scan(&count)
    }

    defer db.Close()
    return count
}

type I interface {
    exec_linux_cmd()
}

func (t *Tester) exec_linux_cmd() {
    cmd := exec.Command("go", `version`)
    out,err := cmd.CombinedOutput()
    if err != nil {
        fmt.Printf("cmd.Run() failed with %s\n", err)
        return
    }
    fmt.Printf("go version:\n%s\n", string(out))
}

func error_catch() { // 必须要先声明defer，否则不能捕获到panic异常
    if err:=recover();err!=nil{
        fmt.Println("Error: ")
        fmt.Println(err) // 这里的err其实就是panic传入的内容，55
        //panic(err)  //让程序直接爆错退出
    }
}

func test_switch_type( obj interface{} ) {
    switch t := obj.(type) {
        case *Tester: //case Tester ?
            fmt.Println("switch/case store Tester :", t)
        case int:
            fmt.Println("switch/case store int :", t)
        default:
            fmt.Println("unknown type !")
    }
}

func main(){
    /*cfg,err := goconfig.LoadConfigFile("../../config/matrix.conf")
    if err != nil {
        fmt.Println(err)
        panic("错误")
    } else {
        fmt.Println(cfg)
    }*/
    //defer error_catch()

    //var tester Tester  //ok
    //tester := Tester() //错误
    //tester := Tester{} //ok
    tester := Tester{ TBase{false},true } //ok
    count := tester.get_table_count()
    fmt.Printf("is begin: %t\n",tester.begin)
    fmt.Printf("is tester: %t\n",tester.is_tester)
    fmt.Println(count)
    tester.exec_linux_cmd()

    //注意I是interface类型，tester是struct
    //var cmder I = new(Tester) //ok https://blog.csdn.net/stpeace/article/details/84037370
    var cmder I = &tester //ok     理解 go interface 的 5 个关键点

    cmder.exec_linux_cmd()

    fmt.Println("+ test if.tpye / switch :")
    if t, ok := cmder.(*Tester); ok {
        fmt.Println("it is Tester obj. ", t)
    }
    //func test_func(){} error!
    test_switch_type(cmder)
    test_switch_type(1)
    test_switch_type("s")
}
