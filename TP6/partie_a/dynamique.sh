set -e
g++ -std=c++23 -I../uin-campus/include -fPIC -c ../uin-campus/src/calculs.cpp -o calculs.o
g++ -std=c++23 -I../uin-campus/include -fPIC -c ../uin-campus/src/regles.cpp -o regles.o
g++ -shared calculs.o regles.o -o libuincalculs.so
g++ -std=c++23 -I../uin-campus/include demo.cpp -L. -luincalculs -o demo_dynamique
LD_LIBRARY_PATH=. ./demo_dynamique
