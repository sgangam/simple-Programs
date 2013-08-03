#CFLAGS=-std=c++0x -O3 -Wall -Werror
CFLAGS=-g -std=c++0x

all: bfsdfs 2dgeo traversals

bfsdfs: bfsdfs.cc
	g++ $(CFLAGS) bfsdfs.cc -o bfsdfs.exe

2dgeo: 2dgeo.cc
	g++ $(CFLAGS) 2dgeo.cc -o 2dgeo.exe

traversals: traversals.cc
	g++ $(CFLAGS) traversals.cc -o traversals.exe
clean:
	rm *.exe

