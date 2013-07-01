/***
 * Author: Sriharsha Gangam
 * ------------------------
 *
 * 4. Transform the Expression
 *
 * Problem code: ONP
 *
 * Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). Operands: only letters: a,b,...,z. Assume that there is only one RPN form (no expressions like a*b*c).
 *
 * Input
 *
 * t [the number of expressions <= 100]
 * expression [length <= 400]
 * [other expressions]
 * Text grouped in [ ] does not appear in the input file.
 *
 * Output
 *
 * The expressions in RPN form, one per line.
 * Example
 *
 * Input:
 * 3
 * (a+(b*c))
 * ((a+b)*(z+x))
 * ((a+t)*((b+(a+c))^(c+d)))
 *
 * Output:
 * abc*+
 * ab+zx+*
 * at+bac++cd+^*
 * */

#include<iostream>
#include<list>
#include<cassert>
#include<cmath>
#include<sstream>
#include<stack>

//Transform the algebraic expression with brackets into RPN form 
class RPNConvertor {
    
    std::string outputExpr;
    std::stack<std::string> stk;
  public:
    RPNConvertor (const std::string & expr) {
        for (int i = 0 ; expr[i] != '\0' ; i++) {
            std::string subExpr = expr.substr(i, 1);
            //std::cout << subExpr << std::endl;
            stk.push(subExpr);
            if (expr[i] == ')') {
                computeRPNSubExpr();
            }
        }
        outputExpr = stk.top();
    }

    void computeRPNSubExpr() {
        std::string closeBracket = stk.top(); stk.pop();
        std::string rightExpr = stk.top(); stk.pop();
        std::string op = stk.top(); stk.pop();
        std::string leftExpr = stk.top(); stk.pop();
        std::string startBracket = stk.top(); stk.pop();
        std::string rpnExpr = leftExpr + rightExpr + op;
        stk.push(rpnExpr);
    }

    void print() {
        std::cout << outputExpr << std::endl;
    }
};



int main(int argc, char *argv[]) {
   
    unsigned int testCount = 0;
    std::string firstLine;
    std::getline(std::cin, firstLine);
    std::stringstream strsm(firstLine);
    strsm >> testCount;
    for (int i = 0; i < testCount ; i++) {
        std::string expr;
        std::getline (std::cin, expr);
        RPNConvertor rpn(expr);
        rpn.print();
    }
    return 0;
}
