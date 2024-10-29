// Jim Lawless
package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
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
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	sum := 0
	for i := 0; i < len(lines); i++ {
		s := lines[i]
		accum := 0
		symFound := false
		for j := 0; j < len(s); j++ {
			if isDigit(s[j]) {
				accum = accum*10 + int(s[j]-'0')
				symFound = symFound || adjacentSym(lines, i-1, j-1)
				symFound = symFound || adjacentSym(lines, i-1, j)
				symFound = symFound || adjacentSym(lines, i-1, j+1)
				symFound = symFound || adjacentSym(lines, i, j+1)
				symFound = symFound || adjacentSym(lines, i+1, j+1)
				symFound = symFound || adjacentSym(lines, i+1, j)
				symFound = symFound || adjacentSym(lines, i+1, j-1)
				symFound = symFound || adjacentSym(lines, i, j-1)

			} else {
				if accum != 0 {
					if symFound {
						sum += accum
					}
				}
				accum = 0
				symFound = false
			}
		}
		if accum != 0 && symFound {
			sum += accum
		}
	}
	fmt.Println(sum)
}

func isDigit(b byte) bool {
	return b >= '0' && b <= '9'
}

func adjacentSym(lin []string, row int, col int) bool {
	if row < 0 || row >= len(lin) {
		return false
	}
	if col < 0 || col >= len(lin[row]) {
		return false
	}
	tmp := lin[row][col]
	if (!isDigit(tmp)) && (tmp != '.') {
		return true
	}
	return false
}
func handleError(e error) {
	if e != nil {
		log.Fatal(e)
		os.Exit(1)
	}
}
