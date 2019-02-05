//https://www.cnblogs.com/golove/p/5909791.html
package main

import (
	"fmt"
	"time"
)

type myError struct {
	err   string
	time  time.Time
	count int
}

func (m *myError) Error() string {
	return fmt.Sprintf("%s %d 次。时间：%v", m.err, m.count, m.time)
}

func newErr(s string, i int) *myError {
	return &myError{
		err:   s,
		time:  time.Now(),
		count: i,
	}
}

var count int

func SomeFunc() error {
	if true {
		count++
		return newErr("遇到某某情况", count)
	}
	return nil
}

func main() {
	for i := 0; i < 5; i++ {
		if err := SomeFunc(); err != nil {
			fmt.Println(err)
		}
	}
}

