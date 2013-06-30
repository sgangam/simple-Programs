/***
 * Author: Sriharsha Gangam
 * ------------------------
 *
 * SPOJ Problem Set (classical)
 *
 * 2. Prime Generator
 *
 * Problem code: PRIME1
 *
 * Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!
 *
 * Input
 *
 * The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.
 *
 * Output
 *
 * For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.
 *
 * Example
 *
 * Input:
 * 2
 * 1 10
 * 3 5
 *
 * Output:
 * 2
 * 3
 * 5
 * 7
 *
 * 3
 * 5
 * */

#include<iostream>
#include<list>
#include<cassert>
#include<cmath>

class PrimesBetween {
    unsigned int maxPrime; // We maintain a list of primes, the maximum prime in our list is given by maxPrime
    std::list<unsigned int> primeList;
    bool isPrime(unsigned int n);
    void updatePrimeList(unsigned int sqend);

  public:
    PrimesBetween () {
        maxPrime = 2;
        primeList.push_back(2); 
    }

    void printPrimes(unsigned int start, unsigned int end) {
        assert(start <= end);
        unsigned int sqend = (unsigned int)(sqrt(end));
        if (maxPrime < sqend) {
            updatePrimeList(sqend); 
        }
        for (int i = start; i <= end; i++){
            if (isPrime(i))
                std::cout << i << std::endl;
        }
    }
};

void PrimesBetween::updatePrimeList(unsigned int sqend) {
    
    for (int i = maxPrime + 1;  i <= sqend; i++) {
        if (isPrime(i))
            primeList.push_back(i);
    }
    maxPrime = sqend;
}

bool PrimesBetween::isPrime(unsigned int n) {
    if (n == 1)
        return false;
    std::list<unsigned int>::const_iterator pit;
    unsigned int sqn = (unsigned int)(sqrt(n));  
    for (pit = primeList.begin(); pit != primeList.end(); ++pit) {
        unsigned int prime = *pit;
        if (prime > sqn)
            break;
        if (n % prime == 0)
            return false;
    }
    return true;
}


int main(int argc, char *argv[]) {
   
    unsigned int testCount = 0;
    unsigned int start = 0;
    unsigned int end = 0;
    std::cin >> testCount;
    PrimesBetween bp;
    for (int i = 0; i < testCount ; i++) {
        std::cin >> start;
        std::cin >> end;
        bp.printPrimes(start, end);
        std::cout << std::endl;
    }

    return 0;
}
