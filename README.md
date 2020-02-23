Create shared object malloc.so from malloc.c
	gcc -o malloc.so -shared -fPIC malloc.c -D_GNU_SOURCE
Create executable main by compiling main.c and linking malloc.so
	gcc -o main main.c ./malloc.so -ldl
