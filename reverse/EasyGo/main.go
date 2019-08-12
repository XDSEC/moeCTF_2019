package main

import (
	"fmt"
)

func main() {
	fmt.Println("Please input the secret number")
	var a int
	var flag string
	flag = "moectf{G0_1Anguage_1s_1nT3r3st1ng}"
	_, _ = fmt.Scanln(&a)
	if (a == 1107) {
		fmt.Println(flag)
	} else {
		fmt.Println("Wrong~");
	}
	_, _ = fmt.Scanln(&a)
}
