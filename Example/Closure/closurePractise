package main

import "fmt"

func createCounter(init int) (add func() int, dec func() int, reset func() int) {
	curVal := init
	add = func() int {
		curVal++
		return curVal
	}

	dec = func() int {
		curVal--
		return curVal
	}

	reset = func() int {
		curVal = init
		return curVal
	}
	return add, dec, reset
}

func main() {
	add, dec, reset := createCounter(5)
	fmt.Println(add())
	fmt.Println(reset())
	fmt.Println(dec())
}

// 6
// 5
// 4
