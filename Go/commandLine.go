package main

import (
	"flag"
	"fmt"
	"os"
)

var name string
var cmdLine = flag.NewFlagSet("", flag.ExitOnError)

func init() {
	cmdLine.Usage = func() {
		_, err := fmt.Fprintf(os.Stderr, "Usage of %s:\n", "question")
		if err != nil {
			return
		}
		cmdLine.PrintDefaults()
	}
	cmdLine.StringVar(&name, "name", "everyone", "The greeting object.")
}

func main() {
	err := cmdLine.Parse(os.Args[1:])
	if err != nil {
		return
	}
	fmt.Printf("Hello, %s!", name)
}
