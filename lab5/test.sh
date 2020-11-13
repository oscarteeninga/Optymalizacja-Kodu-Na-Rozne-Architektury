gcc c/dense.c
go build go/dense.go
echo "===================="
echo "       Dense"
echo "--------------------"
./a.out $1
./dense $1
echo "====================\n"

gcc c/dense0.c
go build go/dense0.go
echo "===================="
echo "       Dense0"
echo "--------------------"
./a.out $1
./dense0 $1
echo "====================\n"

gcc c/dense1.c
go build go/dense1.go
echo "===================="
echo "       Dense1"
echo "--------------------"
./a.out $1
./dense1 $1
echo "====================\n"

gcc c/dense2.c
go build go/dense2.go
echo "===================="
echo "       Dense2"
echo "--------------------"
./a.out $1
./dense2 $1
echo "====================\n"

gcc c/dense3.c
go build go/dense3.go
echo "===================="
echo "       Dense3"
echo "--------------------"
./a.out $1
./dense3 $1
echo "====================\n"

gcc c/dense4.c
go build go/dense4.go
echo "===================="
echo "       Dense4"
echo "--------------------"
./a.out $1
./dense4 $1
echo "====================\n"