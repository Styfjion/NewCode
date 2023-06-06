package main

import (
	"fmt"
	"time"
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
	time.Sleep(time.Nanosecond) //休眠协程，重新调度
	ch3 <- 1                    //异步通道，不阻塞继续执行
	fmt.Println("async channel")
	fmt.Println("f 1")
	fmt.Println("block channel") //同步通道，阻塞执行
	_ = <-ch1
	fmt.Println("unblock channel")
	fmt.Println("f 2")
	ch2 <- 1
}

func main() {
	go f()
	fmt.Println("start")
	_ = <-ch2
	fmt.Println("finish") //同步通道，等待协程
}

//start
//g 1
//async channel
//f 1
//block channel
//g 2
//unblock channel
//f 2
//finish
