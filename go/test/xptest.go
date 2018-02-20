package test

import (
    "encoding/json"
    "fmt"
    "time"
    "reflect"
)

type Person struct {
    Name        string `json:"username"`
    Age         int
    Gender      bool `json:"gender"`
}

func Test() {
    person := Person{
        Name:"Jim",
        Age:4,
        Gender:false,
    }
    fmt.Printf("struct +v: %+v \n", person)
    fmt.Printf("struct #v: %#v \n", person)
    fmt.Printf("struct T: %T \n", person)
    fmt.Printf("struct b: %b \n", person)
    encoded, _ := json.Marshal(person)
    fmt.Printf("json.Marshal: %s \n", string(encoded))
    //fmt.Print(err)
    var decoded map[string]interface{}
    json.Unmarshal(encoded, &decoded)
    fmt.Printf("struct +v: %+v \n", decoded)
    //fmt.Println("data == decoded: ",reflect.DeepEqual(encoded, decoded))
    fmt.Printf("encoded == decoded: %t\n",reflect.DeepEqual(encoded, decoded))
    //fmt.Printf(err)
    //fmt.Printf("%d \n", decoded.Age)
    for i := 1; i <= 3; i++ {
        time.Sleep(250 * time.Millisecond)
        fmt.Printf("for %d \n", i)
    }
}
