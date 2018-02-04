package main
import (
    "net/http"
    "log"
    "./mybase"
)

func main() {
    http.HandleFunc("/", mybase.SayhelloName) //设置访问的路由
    err := http.ListenAndServe(":9090", nil) //设置监听的端口
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
    log.Fatal("ListenAndServer 9090.")
}
