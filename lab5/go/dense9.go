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

func max(a int, b int) uint {
	if a > b {
		return uint(a)
	} else {
		return uint(b)
	}
}

func chol(A matrix, n uint) int {
	var j uint
	var i uint
	var k uint
	var tmp float64
	var arr_i []float64
	var arr_j []float64

	for j = 0; j < n; j++ {
		arr_j = A.m[j]
		for i = j; i < n; i++ {
			arr_i = A.m[i]
			tmp = arr_i[j]
			for k = 0; k < j; {
				if k < max(int(j-8), 0) {
					tmp = tmp - (arr_i[k] * arr_j[k])
					tmp = tmp - (arr_i[k+1] * arr_j[k+1])
					tmp = tmp - (arr_i[k+2] * arr_j[k+2])
					tmp = tmp - (arr_i[k+3] * arr_j[k+3])
					tmp = tmp - (arr_i[k+4] * arr_j[k+4])
					tmp = tmp - (arr_i[k+5] * arr_j[k+5])
					tmp = tmp - (arr_i[k+6] * arr_j[k+6])
					tmp = tmp - (arr_i[k+7] * arr_j[k+7])
					k += 8
				} else {
					tmp = tmp - (arr_i[k] * arr_j[k])
					k += 1
				}
			}
			A.m[i][j] = tmp
		}

		tmp = arr_j[j]
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

// for j = 0; j < n; j++ {
// 	arr_j = A.m[j]
// 	for i = j; i < n; i++ {
// 		for k = 0; k < j; {
// 			if i < max(int(n-8), 0) {
// 				arr_i = A.m[i]
// 				tmp = arr_i[j]
// 				tmp = tmp - (arr_i[k] * arr_j[k])     /*OPT*/
// 				tmp = tmp - (arr_i[k+1] * arr_j[k+1]) /*OPT*/
// 				tmp = tmp - (arr_i[k+2] * arr_j[k+2]) /*OPT*/
// 				tmp = tmp - (arr_i[k+3] * arr_j[k+3]) /*OPT*/
// 				tmp = tmp - (arr_i[k+4] * arr_j[k+4]) /*OPT*/
// 				tmp = tmp - (arr_i[k+5] * arr_j[k+5]) /*OPT*/
// 				tmp = tmp - (arr_i[k+6] * arr_j[k+6]) /*OPT*/
// 				tmp = tmp - (arr_i[k+7] * arr_j[k+7]) /*OPT*/
// 				A.m[i][j] = tmp
// 				k += 8
// 			} else {
// 				A.m[i][j] = A.m[i][j] - (A.m[i][k] * arr_j[k])
// 				k += 1
// 			}
// 		}
// 	}

// 	fmt.Println(tmp)

// 	tmp = arr_j[j]
// 	if tmp < 0.0 {
// 		return (1)
// 	}

// 	A.m[j][j] = math.Sqrt(tmp)

// 	for i = j + 1; i < n; i++ {
// 		A.m[i][j] = A.m[i][j] / tmp
// 	}
// }
// return (0)

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
		fmt.Println("!!!!!!!!!!!error!!!!!!!!!!")
	}
	t2 = makeTimestamp()

	if len(os.Args) > 2 {
		show(A.m, n)
	}

	fmt.Print("GO:\t")
	fmt.Print(float64(t2-t1) / float64(1000000000))
	fmt.Println(" [s]")
}
