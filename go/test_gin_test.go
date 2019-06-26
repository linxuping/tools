package main

import (
    "fmt"
    "bytes"
    "unsafe"
    "reflect"
    "io/ioutil"
    "testing"
    "net/http"
    "encoding/json"
)

type JsonPostSample struct {
}

func (this *JsonPostSample) SamplePost() {
    song := make(map[string]interface{})
    song["arg"] = 12

    //if bytesData, err := json.Marshal(song); err != nil { //can replace bellow two
    bytesData, err := json.Marshal(song) 
    if err != nil {
        fmt.Println(err.Error())
        return
    }
    fmt.Println(bytesData)
    reader := bytes.NewReader(bytesData)
    url := "http://localhost:8001/jump_post"
    req, err := http.NewRequest("POST", url, reader)
    if err != nil {
        fmt.Println(err.Error())
        return
    }
    req.Header.Set("Content-Type", "application/json;charset=UTF-8")
    client := http.Client{}
    resp, err := client.Do(req)
    if err != nil {
        fmt.Println(err.Error())
        return
    }   
    fmt.Println("resp body: ", resp.Body)
    respBytes, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        fmt.Println(err.Error())
        return
    }
    str := (*string)(unsafe.Pointer(&respBytes))
    fmt.Println("resp body bytes: ", *str)

    var unjson map[string]interface{}
    json.Unmarshal(respBytes, &unjson)
    fmt.Println("Unmarshal resp body json: ", unjson)
    for k,v := range unjson {
        fmt.Println("item: ", k, v, reflect.TypeOf(v))
    }

    Unmarshal_Number := func(r []byte, ret interface{})  {
        decoder := json.NewDecoder(bytes.NewReader(r))
        decoder.UseNumber()
        if err := decoder.Decode(&ret); err != nil {
            fmt.Println("Unmarshal_Number error", err)
        }
    }
    Unmarshal_Number(bytesData, &unjson)
    //http://ju.outofmemory.cn/entry/346501
    fmt.Println("保证int解析：Unmarshal_Number body json: ", unjson)
    for k,v := range unjson {
        fmt.Println("item: ", k, v, reflect.TypeOf(v))
        //if reflect.TypeOf(v) == json.Number {
        switch v.(type) {
            case json.Number:
                if _v, err := v.(json.Number).Int64(); err == nil {
                    fmt.Println("is Number: ", _v, reflect.TypeOf(_v))
                }
        }
    }
}

func TestSamplePost(t *testing.T) {
    fmt.Println(123)
    sample := new(JsonPostSample)
    sample.SamplePost()
}


