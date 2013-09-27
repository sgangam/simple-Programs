/***
 * Author: Sriharsha Gangam
 * ------------------------
 * */

#include<iostream>
#include<cstdlib>
#include<list>
#include<string>
#include<sstream>
#include<cassert>
#include<cmath>
#include <unordered_map>


bool compareNum(std::string first, std::string second) {
    int fir = atoi(first.c_str());
    int sec = atoi(second.c_str());
    if (fir < sec)
        return true;
    else 
        return false;
}


int main(int argc, char *argv[]) {
    std::list<std::string> alphaStrings;
    std::list<std::string> numStrings;
    // store individual strings in two  separate strings.
    std::string expr, str;
    //read the line from std input
    std::getline (std::cin, expr);
    std::stringstream  lineStream(expr);
    std::list<bool> numBoolList; // A list which maintains the list of indices that cantain numbers.
    while(lineStream >> str) {
        if (str[0] >= 'a' && str[0] <= 'z') {
            alphaStrings.push_back(str);
            numBoolList.push_back(false);
        }
        else{
            numStrings.push_back(str);
            numBoolList.push_back(true);
        }
    }
    alphaStrings.sort();
    numStrings.sort(compareNum);

    std::list<std::string>::iterator numIt = numStrings.begin();
    std::list<std::string>::iterator alphaIt = alphaStrings.begin();
    std::list<bool>::iterator numBoolIt = numBoolList.begin();

    while (numBoolIt != numBoolList.end()) {

        if (*numBoolIt == true){ // is it a number 
            //std::cout <<" num";
            std::cout << *numIt << " ";
            numIt++;
        }
        else {
            //std::cout <<" alph";
            std::cout << *alphaIt << " ";
            alphaIt++;
        }
        numBoolIt++; 
    }
    std::cout << std::endl;

    return 0;
}
