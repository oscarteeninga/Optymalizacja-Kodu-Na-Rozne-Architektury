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

func max(a int, b int) uint {
	if a > b {
		return uint(a)
	} else {
		return uint(b)
	}
}

func chol(A []float64, n uint) int {
	var j uint
	var i uint
	var k uint
	var tmp float64

	for j = 0; j < n; j++ {
		for i = j; i < n; i++ {
			if j > 0 {
				tmp = A[IDX(i, j, n)]
				for k = j - 1; k > 0; k-- { /*OPT*/
					tmp = tmp - (A[IDX(i, k, n)] * A[IDX(j, k, n)])
				}
				tmp = tmp - (A[IDX(i, 0, n)] * A[IDX(j, 0, n)])
				A[IDX(i, j, n)] = tmp
			}
		}
		tmp = A[IDX(j, j, n)]
		if tmp < 0.0 {
			return (1)
		}
		tmp = math.Sqrt(tmp)
		A[IDX(j, j, n)] = tmp
		for i = j + 1; i < n; i++ {
			A[IDX(i, j, n)] = A[IDX(i, j, n)] / tmp
		}
	}
	return (0)
}

func show(A []float64, n uint) {
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
	var A []float64 = make([]float64, n*n)

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
