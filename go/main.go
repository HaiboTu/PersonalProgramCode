package main

import "fmt"

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range &s {
		sum += v
	}
	c <- sum // send sum to channel
}

func main() {
	go say("world")
	say("hello")
}

