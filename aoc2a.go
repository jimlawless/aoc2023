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

var patGrammar = "([\\d]+|red|green|blue)"
var reGrammar *regexp.Regexp

func main() {
	file, err := os.Open(os.Args[1])
	handleError(err)
	defer func() {
		if err = file.Close(); err != nil {
			log.Fatal(err)
		}
	}()
	scanner := bufio.NewScanner(file)
	reGrammar, _ = regexp.Compile(patGrammar)

	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		tokens := reGrammar.FindAllString(line, -1)
		gameNum, _ := strconv.Atoi(tokens[0])
		redMax := 0
		greenMax := 0
		blueMax := 0

		i := 1
		for ; i < (len(tokens) - 1); i += 2 {
			tmp, _ := strconv.Atoi(tokens[i])
			switch {
			case tokens[i+1] == "red":
				if tmp > redMax {
					redMax = tmp
				}
			case tokens[i+1] == "green":
				if tmp > greenMax {
					greenMax = tmp
				}
			case tokens[i+1] == "blue":
				if tmp > blueMax {
					blueMax = tmp
				}
			}
		}
		if redMax <= 12 && greenMax <= 13 && blueMax <= 14 {
			fmt.Println("Game ", gameNum, redMax, greenMax, blueMax)
			sum += gameNum
		}
	}
	fmt.Println(sum)
}

func handleError(e error) {
	if e != nil {
		log.Fatal(e)
		os.Exit(1)
	}
}
