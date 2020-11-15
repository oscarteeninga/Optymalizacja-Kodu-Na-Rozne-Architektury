package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"time"
)

type matrix struct {
	m [][]float64
}

func makeTimestamp() int64 {
	return time.Now().UnixNano()
}
func chol(A matrix, n uint) int {
	var j uint
	var i uint
	var k uint
	var tmp float64

	for j = 0; j < n; j++ {
		for i = j; i < n; i++ {
			var tmp = A.m[i][j]
			for k = 0; k < j; k++ {
				tmp = tmp - (A.m[i][k] * A.m[j][k])
			}
			A.m[i][j] = tmp
		}

		tmp = A.m[j][j]
		if tmp < 0.0 {
			return (1)
		}

		tmp = math.Sqrt(tmp)
		A.m[j][j] = tmp

		for i = j + 1; i < n; i++ {
			A.m[i][j] = A.m[i][j] / tmp
		}
	}
	return (0)
}

func show(A [][]float64, n uint) {
	var i uint
	var j uint
	for i = 0; i < n; i++ {
		for j = 0; j < n; j++ {
			fmt.Print(A[i][j])
		}
		fmt.Println()
	}
}

func main() {
	nx, _ := strconv.Atoi(os.Args[1])
	var n uint = uint(nx)
	var t1 int64
	var t2 int64
	var m [][]float64 = make([][]float64, n) /*OPT*/
	var A matrix = matrix{m: m}              /*OPT*/
	var h uint
	for h = 0; h < n; h++ {
		A.m[h] = make([]float64, n)
	}

	var i uint
	for i = 0; i < n-1; i++ {
		A.m[i][i] = 2.0
		A.m[i+1][i] = 1.0
		A.m[i][i+1] = 1.0
	}
	A.m[n-1][n-1] = 2.0

	if len(os.Args) > 2 {
		show(A.m, n)
	}

	t1 = makeTimestamp()
	if chol(A, n) != 0 {
		fmt.Println("error")
	}
	t2 = makeTimestamp()

	if len(os.Args) > 2 {
		show(A.m, n)
	}

	fmt.Print("GO:\t")
	fmt.Print(float64(t2-t1) / float64(1000000000))
	fmt.Println(" [s]")
}
