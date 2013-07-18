all:
	g++ -std=c++0x -O3 -Wall -Werror bfsdfs.cc -o bfsdfs.exe
clean:
	rm *.exe

