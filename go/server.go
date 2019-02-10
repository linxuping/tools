package main

import (
	"./mybase"
	"./test"
	"fmt"
	"log"
	"net/http"
)

func main() {
	if true {
		http.HandleFunc("/ptest", test.FetchPage)      //压测:ab -c 100 -n 100  http://localhost:9090/ptest
		http.HandleFunc("/hello", mybase.SayhelloName) //设置访问的路由
		err := http.ListenAndServe(":9090", nil) //设置监听的端口
		if err != nil {
			log.Fatal("ListenAndServe: ", err)
		}
		log.Fatal("ListenAndServer 9090.")
	}

	if true {
		//test.RedisTest()
		//test.Test()
		//test.TestChan()
		test.TestSelectChan()
		//test.Test2ChanAndGo()
		return
	}

	funcs := map[string]func(){"testfunc": test.Testfunc}
	//test.Testfunc() //ok
	//funcs['testfunc']() //error
	//funcs[`testfunc`]() //ok
	funcs["testfunc"]() //test.Testfunc()

	str := `
    你好!
    world`
	fmt.Println(str)

	go test.Coroutine1()
	go test.Coroutine2()

}
