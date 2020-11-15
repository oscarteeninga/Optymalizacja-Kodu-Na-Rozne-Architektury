go build dense.go
echo "===================="
echo "       Dense"
echo " Brak optymalizacji "
echo "--------------------"
./dense $1 $2
echo "====================\n"

go build dense0.go
echo "===================="
echo "       Dense0"
echo " Uzycie tmp do petli"
echo "--------------------"
./dense0 $1 $2
echo "====================\n"

go build dense1.go
echo "===================="
echo "       Dense1"
echo " Zmiana typu na int "
echo "--------------------"
./dense1 $1 $2
echo "====================\n"

go build dense2.go
echo "===================="
echo "       Dense2"
echo "    Dekrementacja   "
echo "--------------------"
./dense2 $1 $2
echo "====================\n"

go build dense3.go
echo "===================="
echo "       Dense3"
echo " Rozwiniecie petli 8"
echo "--------------------"
./dense3 $1 $2
echo "====================\n"

go build dense4.go
echo "===================="
echo "       Dense4"
echo "Rozwiniecie petli 16"
echo "--------------------"
./dense4 $1 $2
echo "====================\n"

go build dense5.go
echo "===================="
echo "       Dense5"
echo "Rozwiniecie petli 32"
echo "--------------------"
./dense5 $1 $2
echo "====================\n"

go build dense6.go
echo "===================="
echo "       Dense6"
echo "  Struktura matrix  "
echo "--------------------"
./dense6 $1 $2
echo "====================\n"

go build dense7.go
echo "===================="
echo "       Dense7"
echo "     Uzycie tmp"
echo "--------------------"
./dense7 $1 $2
echo "====================\n"

go build dense8.go
echo "===================="
echo "       Dense8"
echo "Uzycie tmp dla array"
echo "--------------------"
./dense8 $1 $2
echo "====================\n"

go build dense9.go
echo "===================="
echo "       Dense9"
echo "      Blok 1x8"
echo "--------------------"
./dense9 $1 $2
echo "====================\n"

go build dense10.go
echo "===================="
echo "       Dense10"
echo "      Blok 8x8"
echo "--------------------"
./dense10 $1 $2
echo "====================\n"

echo "===================="
echo "Dense: "
./dense $1 $2
echo "Dense0: "
./dense0 $1 $2
echo "Dense1: "
./dense1 $1 $2
echo "Dense2: "
./dense2 $1 $2
echo "Dense3: "
./dense3 $1 $2
echo "Dense4: "
./dense4 $1 $2
echo "Dense5: "
./dense5 $1 $2
echo "Dense6: "
./dense6 $1 $2
echo "Dense7: "
./dense7 $1 $2
echo "Dense8: "
./dense8 $1 $2
echo "Dense9: "
./dense9 $1 $2
echo "Dense10: "
./dense10 $1 $2