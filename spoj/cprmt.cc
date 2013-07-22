/***
 * Author: Sriharsha Gangam
 * ------------------------
 *  of lowercase letters, a and b, print the longest string x of lowercase letters such that there is a permutation of x that is a subsequence of a and there is a permutation of x that is a subsequence of b.
 *
 *  Input
 *
 *  Input file contains several lines of input. Consecutive two lines make a set of input. That means in the input file line 1 and 2 is a set of input, line 3 and 4 is a set of input and so on. The first line of a pair contains a and the second contains b. Each string is on a separate line and consists of at most 1000 lowercase letters.
 *
 *  Output
 *
 *  For each set of input, output a line containing x. If several x satisfy the criteria above, choose the first one in alphabetical order.
 *
 *  Example
 *
 *  Sample input:
 *  pretty
 *  women
 *  walking
 *  down
 *  the
 *  street
 *   
 *   Sample output:
 *   e
 *   nw
 *   et 
 *
 * */

#include<iostream>
#include<cassert>
#include<cmath>
#include<sstream>
#include<algorithm>

#define ALPH_SIZE 26
class CommonPermutation {
        std::string str1, str2;
        int array1[ALPH_SIZE];
        int array2[ALPH_SIZE];
        std::stringstream ssResult;
    public:
        std::string result;
        CommonPermutation(const std::string & s1, const std::string & s2) {
            this->str1 = s1;
            this->str2 = s2;
            for (int i = 0; i < ALPH_SIZE; i++) {
                array1[i] = 0;
                array2[i] = 0;
            }
            for (int i = 0; str1[i] != '\0'; i++)
                array1[str1[i] - 'a' ]++;
            for (int i = 0; str2[i] != '\0'; i++)
                array2[str2[i] - 'a']++;

            for (int i = 0; i < ALPH_SIZE; i++) {
                //std::cout << array1[i] << " " << array2[i] << std::endl;
                while ((array1[i]--) > 0 && (array2[i]--) > 0) {
                    ssResult << char(i + 'a');
                }
            }
            result = ssResult.str();
            std::sort(result.begin(), result.end());
        }
};

int main(int argc, char *argv[]) {
   
    std::string s1;
    std::string s2; 
    while(getline(std::cin, s1)) {
        getline(std::cin, s2);
        CommonPermutation cp(s1, s2);
        std::cout << cp.result << std::endl;
    }
    return 0;
}
