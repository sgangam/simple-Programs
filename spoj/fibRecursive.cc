/***
 * Author: Sriharsha Gangam
 * ------------------------
 12009. Fibonacci recursive sequences (hard)

 Problem code: FRSKH

 Leo searched for a new fib-like problem, and ...
 it's not a fib-like problem that he found !!! Here it is.

 Let FIB the Fibonacci function :
 FIB(0)=0 ; FIB(1)=1
 and
 for N>=2 FIB(N) = FIB(N-1) + FIB(N-2)
Example : we have FIB(6)=8, and FIB(8)=21.

Let F(K, N) a new function: 
F(0, N) = N for all integers N.
F(K, N) = F(K-1, FIB(N) ) for K>0 and all integers N.

Example : F(2, 6) = F(1, FIB(6) ) = F(0, FIB( FIB(6) ) ) = FIB( FIB(6) ) = FIB(8) = 21

Input

The input begins with the number T of test cases in a single line.
In each of the next T lines there are three integers: K, N, M.

Output

For each test case, print F(K, N),
as the answer could not fit in a 64bit container,
give your answer modulo M.
Example

Input:
3
4 5 1000
3 4 1000
2 6 1000

Output:
5
1
21
Constraints

1 <= T <= 10^3
0 <= K <= 10^18
0 <= N <= 10^18
2 <= M <= 10^18
K, N, M are uniform randomly chosen.

 * */

#include<iostream>
#include<cassert>

class RevFib {
    unsigned long long int modulo; 
    unsigned long long fibonacci(unsigned long long int maxIndex);
    unsigned long long fibnPrev;
    unsigned long long fibN;
    unsigned long long N;

  public:
    unsigned long long int result; 
    RevFib(unsigned long long int iK, unsigned long long int iN, unsigned long long int imodulo) {
        this->modulo = imodulo;  
        this->N = 1;
        fibnPrev = 0;
        fibN = 1;

        unsigned long long int currN = iN;
        for (long long int i = iK; i > 0; --i) {
            currN = fibonacci(currN);
        }
        result = currN % modulo;
    }
};

unsigned long long RevFib::fibonacci(unsigned long long int maxIndex) {
    if (maxIndex == 0)
        return 0;

    for (; N < maxIndex ; N++) {
        unsigned long long int newfn2 = (fibnPrev + fibN);
        fibnPrev = fibN;
        fibN = newfn2;
    }
    //std::cout << fibnPrev << " " << fibN << " " << N;
    return fibN;
}

int main(int argc, char *argv[]) {
   
    unsigned long long int testCount = 0;
    unsigned long long int K = 0;
    unsigned long long int N = 0;
    unsigned long long int modulo = 0;
    std::cin >> testCount;
    for (long long int i = 0; i < testCount ; i++) {
        std::cin >> K;
        std::cin >> N;
        std::cin >> modulo;
        RevFib rfib(K, N, modulo);
        std::cout << rfib.result << std::endl;
    }

    return 0;
}
