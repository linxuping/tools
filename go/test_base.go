package main

import (
	"fmt"
	"reflect"
)

func main() {
	//*** format ***
	a := 'm'
	b := 1.23
	fmt.Printf("%T %c %v \n", a, a, a)
	fmt.Printf("%T %f %v \n", b, b, b)

	if a := 10; a == 10 {
		fmt.Println("a == 10")
	}

	//*** assign ***
	/*var (
	    a int
	    b string
	  )
	  const (
	    c int
	  )
	  var (
	    d  = 'a' //自动推导类型
	  )
	  a, b, c := 1, 2, 3
	  a, b := b, a  //swap
	*/

	//*** for ***
	//var lis [6]int = { 2,4,6,8,10,12 }  ???
	lis := [6]int{2, 4, 6, 8, 10, 12}
	for i, x := range lis {
		fmt.Printf("%d %v %v\n", i, x, reflect.TypeOf(x))
	}

	//*** slice ***
	var sli []int
	fmt.Printf("%v len:%d cap:%d \n", sli, len(sli), cap(sli))
	sli = append(sli, 1)
	fmt.Printf("%v len:%d cap:%d \n", sli, len(sli), cap(sli))
	sli = append(sli, 1)
	fmt.Printf("%v len:%d cap:%d \n", sli, len(sli), cap(sli))
	sli = append(sli, 1)
	sli = append(sli, 1)
	fmt.Printf("%v len:%d cap:%d \n", sli, len(sli), cap(sli))
	sli = append(sli, 1)
	fmt.Printf("%v len:%d cap:%d \n", sli, len(sli), cap(sli))
	//copy to new
	var sli2 []int
	sli3 := make([]int, len(sli), cap(sli)*2)
	sli4 := make([]int, len(sli)/2, cap(sli)/2)
	fmt.Printf("初始化make slice: sli3=sli*2 %v len:%d cap:%d \n", sli3, len(sli3), cap(sli3))
	fmt.Printf("初始化make slice: sli4=sli/2 %v len:%d cap:%d \n", sli4, len(sli4), cap(sli4))
	retlen2 := copy(sli2, sli)  
	retlen3 := copy(sli3, sli)  
	retlen4 := copy(sli4, sli)  
	fmt.Printf("sli2 %v len:%d cap:%d ret:%d 需要有空间才能copy \n", sli2, len(sli2), cap(sli2), retlen2)
	fmt.Printf("sli3 %v len:%d cap:%d ret:%d\n", sli3, len(sli3), cap(sli3), retlen3)
	fmt.Printf("sli4 %v len:%d cap:%d ret:%d 空间不足被截断 \n", sli4, len(sli4), cap(sli4), retlen4)

	arr := [...]int{1,2,3,4,5}
	fmt.Printf("...数组自动计算长度：%v\n", arr)
	fmt.Printf("before append(sli4,sli...)：%v %v\n", sli4, sli)
	sli4 = append(sli4, sli...)
	fmt.Printf("append(sli4,sli...)：%v len:%d cap:%d\n", sli4, len(sli4), cap(sli4))
	//sli5 := [3]int{}
	//sli5 = sli4 //cannot use sli4 (type []int) as type [3]int in assignment

	//for
	pos := 1
	for {
		pos += 1
		fmt.Println(pos)
		if pos >= 3 {
			break
		}
	}

	//pointer
	//arr = {1,2,3,4,5,6} //
	fmt.Printf("ori:%p type:%T %v cap:%d\n", arr, arr, arr, cap(arr))
	arr1 := arr[0:1]
	arr2 := arr[0:1:1]
	fmt.Printf("arr1.cap:%d arr2.cap:%d\n", cap(arr1), cap(arr2))
	arr1 = append(arr1, 101) 
	fmt.Printf("arr[0:1] append后地址: %p type:%T 现数组:%v 原数组:%p （影响原数组）\n", arr1, arr1, arr1, arr)
	arr2 = append(arr2, 201) 
	fmt.Printf("arr[0:1:1] append后地址: %p type:%T 现数组:%v 原数组ri:%p （不影响原数组）\n", arr2, arr2, arr2, arr)

}
