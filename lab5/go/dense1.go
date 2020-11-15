package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"time"
)

func makeTimestamp() int64 {
	return time.Now().UnixNano()
}

func IDX(i uint, j uint, n uint) uint {
	return j + i*n
}

func chol(A []int /*OPT*/, n uint) int {
	var j uint
	var i uint
	var k uint
	var tmp int /*OPT*/

	for j = 0; j < n; j++ {
		for i = j; i < n; i++ {
			tmp = A[IDX(i, j, n)]
			for k = 0; k < j; k++ {
				tmp = tmp - (A[IDX(i, k, n)] * A[IDX(j, k, n)])
			}
			A[IDX(i, j, n)] = tmp
		}
		var real float64 = float64(A[IDX(j, j, n)])
		if real < 0.0 {
			return (1)
		}
		real = math.Sqrt(real)
		A[IDX(j, j, n)] = int(real)
		for i = j + 1; i < n; i++ {
			A[IDX(i, j, n)] = int(float64(A[IDX(i, j, n)]) / real)
		}
	}
	return (0)
}

func show(A []int, n uint) {
	var i uint
	var j uint
	for i = 0; i < n; i++ {
		for j = 0; j < n; j++ {
			fmt.Print(A[IDX(i, j, n)])
		}
		fmt.Println()
	}
}

func main() {
	nx, _ := strconv.Atoi(os.Args[1])
	var n uint = uint(nx)
	var t1 int64
	var t2 int64
	var A []int = make([]int, n*n) /*OPT*/

	var i uint
	for i = 0; i < n-1; i++ {
		A[IDX(i, i, n)] = 2.0
		A[IDX(i, i+1, n)] = 1.0
		A[IDX(i+1, i, n)] = 1.0
	}
	A[IDX(n-1, n-1, n)] = 2.0

	if len(os.Args) > 2 {
		show(A, n)
	}

	t1 = makeTimestamp()
	if chol(A, n) != 0 {
		fmt.Println("error")
	}
	t2 = makeTimestamp()

	if len(os.Args) > 2 {
		show(A, n)
	}

	fmt.Print("GO:\t")
	fmt.Print(float64(t2-t1) / float64(1000000000))
	fmt.Println(" [s]")
}
