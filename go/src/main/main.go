package main

import (
	"log"
	"pkg"
)

var HelloWord = "Hello world!"

func main() {
	a,b:=3,2

	c,d:=pkg.Swap(a,b)

	log.Printf("a %d, b %d <------> c %d, d %d", a, b, c, d)

	return
}

