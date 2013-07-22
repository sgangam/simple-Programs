all:	bfsdfs 2dgeo

bfsdfs: bfsdfs.cc
	g++ -std=c++0x -O3 -Wall -Werror bfsdfs.cc -o bfsdfs.exe
2dgeo:  2dgeo.cc
	g++ -std=c++0x -O3 -Wall -Werror 2dgeo.cc -o 2dgeo.exe
clean:
	rm *.exe

