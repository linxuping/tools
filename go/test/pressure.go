package test

import (
    "fmt"
    //"time"
    "bytes"
    "reflect"
    "math/rand"
    "net/http"
)

func FetchPage(w http.ResponseWriter, r *http.Request) {
    fmt.Println("into...")
    url := "http://www.baidu.com/"
    num := rand.Int31n(10)
    //time.Sleep(time.Duration(num) * time.Second)
    resp,err := http.Get(url)
    if err != nil {
        fmt.Println(err)
        return
    }
    defer resp.Body.Close()
    fmt.Printf("resp status %s,statusCode %d\n", resp.Status, resp.StatusCode)
    fmt.Printf("resp content length %d\n", resp.ContentLength)
    fmt.Printf("resp transfer encoding %v\n", resp.TransferEncoding)
    fmt.Println(reflect.TypeOf(resp.Body)) 
    buf := bytes.NewBuffer( make([]byte,0,512) )
    length,_ := buf.ReadFrom(resp.Body)
    fmt.Printf("resp content length %d\n", length)
    //fmt.Printf("resp content %s\n", string(buf.Bytes()) )
    fmt.Printf("num %d\n", num )
}


