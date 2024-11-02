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

type Card struct {
	Count int
	Value string
}

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
	var cards []Card
	cards = append(cards, Card{-1, "dummy"})

	for scanner.Scan() {
		line := scanner.Text()
		cards = append(cards, Card{1, line})
	}
	for j := 1; j < len(cards); j++ {
		have := make(map[int]int)
		tokens := reScratch.FindAllString(cards[j].Value, -1)
		i := 1
		for ; i < len(tokens); i++ {
			if tokens[i] == "|" {
				break
			}
			tmp, _ := strconv.Atoi(tokens[i])
			have[tmp] = 1
		}
		counter := 0
		for i = i + 1; i < len(tokens); i++ {
			tmp2, _ := strconv.Atoi(tokens[i])
			if have[tmp2] == 1 {
				if counter == 0 {
					counter = 1
				} else {
					counter = counter + 1
				}
			}
		}
		if counter != 0 {
			for i = j + 1; i <= j+counter; i++ {
				cards[i].Count = cards[i].Count + cards[j].Count
			}
		}
		sum += cards[j].Count
	}
	fmt.Println(sum)
}

func handleError(e error) {
	if e != nil {
		log.Fatal(e)
		os.Exit(1)
	}
}
