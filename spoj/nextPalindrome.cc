/***
 * Author: Sriharsha Gangam
 * ------------------------
 *  Given a  number. It returns a next largest palindrome.
 * Input
 *
 * The first line contains integer t, the number of test cases. Integers K are given in the next t lines.
 *
 * Output
 *
 * For each K, output the smallest palindrome larger than K.
 *
 * Example
 *
 * Input:
 * 2
 * 808
 * 2133
 *
 * Output:
 * 818
 * 2222
 *
 * Warning: large Input/Output data, be careful with certain languages
 *
 * */

#include<iostream>
#include<cassert>
#include<cmath>

class LargestPalindrome {
    
    unsigned int input;
    unsigned int palindrome;
    unsigned int digits;
    unsigned int left;
    void getDigits();
    void constructPalindrome();
  public:
    void printPalindrome();
    LargestPalindrome(unsigned int num) {
        input = num;
        getDigits();
        left = input;
        for (unsigned int i = 0; i < (digits/2); i++)
            left = left/10;

        constructPalindrome();
        if (palindrome < input) {
            left++;
            constructPalindrome();
        }
    }

};

void LargestPalindrome::constructPalindrome() {
    unsigned int num = left;
    palindrome = left;
    unsigned int threshold = pow(10, digits/2);
    while (num >= threshold)
        num /= 10;
    while (num > 0) {
        palindrome = (palindrome * 10) + (num % 10);
        num /= 10;
    }

}

void LargestPalindrome::printPalindrome() {
    std::cout << palindrome ;
}

void LargestPalindrome::getDigits(){ 
    digits = 0;
    unsigned num = input;
    while (num > 0) {
        num = (unsigned int) num/10;
        digits++;
    }
}

int main(int argc, char *argv[]) {
   
    unsigned int testCount = 0;
    unsigned int num = 0;
    std::cin >> testCount;
    for (int i = 0; i < testCount ; i++) {
        std::cin >> num;
        LargestPalindrome lp(num + 1);
        lp.printPalindrome();
        std::cout << std::endl;
    }
    return 0;
}
