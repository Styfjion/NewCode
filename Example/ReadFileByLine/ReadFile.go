package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("test.env")
	if err != nil {
		fmt.Println(err)
		return
	}

	fileScanner := bufio.NewScanner(file)
	var retArray []string
	for fileScanner.Scan() {
		splitPart := strings.Split(fileScanner.Text(), "=")[0]
		retArray = append(retArray, splitPart)
	}
	retStr := strings.Join(retArray, ",")
	fmt.Println(retStr)
}
