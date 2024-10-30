// Jim Lawless
package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
)

var patScratch = "([\\d]+|\\|)"
var reScratch *regexp.Regexp

func main() {
	file, err := os.Open(os.Args[1])
	handleError(err)
	defer func() {
		if err = file.Close(); err != nil {
			log.Fatal(err)
		}
	}()
	scanner := bufio.NewScanner(file)
	reScratch, _ = regexp.Compile(patScratch)

	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		have := make(map[int]int)
		tokens := reScratch.FindAllString(line, -1)
		cardNum, _ := strconv.Atoi(tokens[0])
		i := 1
		for ; i < len(tokens); i++ {
			if tokens[i] == "|" {
				break
			}
			tmp, _ := strconv.Atoi(tokens[i])
			have[tmp] = 1
		}
		value := 0
		for i = i + 1; i < len(tokens); i++ {
			tmp2, _ := strconv.Atoi(tokens[i])
			if have[tmp2] == 1 {
				if value == 0 {
					value = 1
				} else {
					value *= 2
				}
			}
		}
		fmt.Println("Card # ", cardNum, " ", value)
		sum += value
	}
	fmt.Println(sum)
}

func handleError(e error) {
	if e != nil {
		log.Fatal(e)
		os.Exit(1)
	}
}
