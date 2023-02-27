all: buildall runall

m64:
	gcc main.c ../chooks.c -m64 -o build/main64.exe

m32:
	gcc main.c ../chooks.c -m32 -o build/main32.exe

buildall: m32 m64

run32:
	build/main32.exe

run64:
	build/main64.exe

runall: run32 run64
