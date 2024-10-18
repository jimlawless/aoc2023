// Jim Lawless
package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	file, err := os.Open(os.Args[1])
	handleError(err)
	defer func() {
		if err = file.Close(); err != nil {
			log.Fatal(err)
		}
	}()
	scanner := bufio.NewScanner(file)
	accum := 0
	for scanner.Scan() {
		first := ""
		last := ""
		s := scanner.Text()
		for i := 0; i < len(s); i++ {
			digit := ""
			if s[i] >= '0' && s[i] <= '9' {
				digit = string(s[i])
			}
			if digit != "" {
				if first == "" {
					first = digit
				}
				last = digit
			}
		}
		ans, _ := strconv.Atoi(first + last)
		accum += ans
	}
	fmt.Println("Total: ", accum)
}

func handleError(e error) {
	if e != nil {
		log.Fatal(e)
		os.Exit(1)
	}
}
