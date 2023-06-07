package main

import (
	"fmt"
)

var ch1 = make(chan int)
var ch2 = make(chan int)
var ch3 = make(chan int, 1)

func g() {
	fmt.Println("g 1")
	_ = <-ch3
	fmt.Println("g 2")
	ch1 <- 1
}

func f() {
	go g()
	fmt.Println("f 1")
	ch3 <- 1 //异步通道，不阻塞继续执行
	fmt.Println("async channel")
	_ = <-ch1
	fmt.Println("block channel") //同步通道，阻塞执行
	fmt.Println("f 2")
	ch2 <- 1
}

func main() {
	go f()
	fmt.Println("start")
	_ = <-ch2
	fmt.Println("finish") //同步通道，等待协程
}

// output:
// start
// f 1
// g 1
// g 2
// async channel
// block channel
// f 2
// finish
// 说明：f 1和g 1的打印顺序不确定
