set -e
g++ -std=c++23 -I../uin-campus/include -c ../uin-campus/src/calculs.cpp -o calculs.o
g++ -std=c++23 -I../uin-campus/include -c ../uin-campus/src/regles.cpp -o regles.o
ar rcs libuincalculs.a calculs.o regles.o
g++ -std=c++23 -I../uin-campus/include demo.cpp -L. -luincalculs -o demo_statique
./demo_statique
