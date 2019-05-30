package main

import (
	"io"
	"fmt"
	"net"
	"log"
	"time"
)

func handleConn(c net.Conn){
	for {
		_,err := io.WriteString(c, time.Now().String()+"\n")
		if err != nil {
			log.Fatal(err)
		}
		time.Sleep(time.Second)
	}
}

func main () {
	fmt.Println("start listen... ...")
	listener,err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn,err := listener.Accept()
		if err != nil {
			log.Fatal(err)
		}
		go handleConn(conn)
	}
}