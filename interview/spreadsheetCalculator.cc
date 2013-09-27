/***
 * Author: Sriharsha Gangam
 * ------------------------
 *
 * */

#include<iostream>
#include<sstream>
#include<list>
#include <set>
#include <stack>
#include<cassert>
#include<cstdlib>

class Cell;

// A 2 D array of cells. Globally accessible.
Cell **allCells;

//The main datastructure, a cell. Contains refereces to other cells based on dependencies.
class Cell {
    unsigned int row;
    unsigned int column;

    std::list<std::string> expression;
    std::set<Cell*> evaluates; // The set of other cells which use the current cell for evaluation.
    std::set<Cell*> dependsOn; // These cells that have to be computed before the current one can be evaluated. The current cell depends on these.

    void updateSets(std::string elem) {
        if (elem[0] >= 65 && elem[0] <= 90) {
            unsigned int erow = elem[0] - 65; // 'A' is index 0 and so on.
            unsigned int ecol = atoi(&elem[1]) - 1; // Our index starts at 0 instead of 1
            //std::cout << erow << " " << ecol << " " << elem << std::endl;
            if (erow == row && ecol == column) {
                std::cout << "Cyclic dependencies found. Could not compute all the cells" << std::endl;
                exit(1);
            }
            Cell* otherCell = &allCells[erow][ecol];
            dependsOn.insert(otherCell);
            otherCell->evaluates.insert(this);
        }
    }

    void computeRPN() {

        std::stack<float> rpnStack;
        for (std::list<std::string>::iterator it = expression.begin() ; it != expression.end() ; it++) {
            //std::cout  << *it << " " ;
            std::string subexpr = *it; 
            float subexprValue = 0;
            switch (subexpr[0]) {
                case '+': {
                    float second = rpnStack.top(); 
                    rpnStack.pop();
                    float first = rpnStack.top(); 
                    rpnStack.pop();
                    rpnStack.push(first + second);
                    //std::cout  <<  first <<  subexpr[0] << second << rpnStack.top() <<  std::endl; 
                    break;}
                case '-': {
                    float second = rpnStack.top(); 
                    rpnStack.pop();
                    float first = rpnStack.top(); 
                    rpnStack.pop();
                    rpnStack.push(first - second);
                    //std::cout  <<  first <<  subexpr[0] << second << rpnStack.top() <<  std::endl; 
                    break;}
                case '*': {
                    float second = rpnStack.top(); 
                    rpnStack.pop();
                    float first = rpnStack.top(); 
                    rpnStack.pop();
                    rpnStack.push(first * second);
                    //std::cout  <<  first <<  subexpr[0] << second << rpnStack.top() <<  std::endl; 
                    break; }
                case '/': {
                    float second = rpnStack.top(); 
                    rpnStack.pop();
                    float first = rpnStack.top(); 
                    rpnStack.pop();
                    rpnStack.push(first / second);
                    //std::cout  <<  first <<  subexpr[0] << second << rpnStack.top() <<  std::endl; 
                    break;}

                default: // We have an actual float number.
                    if (subexpr[0] >= 65 && subexpr[0] <= 90) {
                        unsigned int erow = subexpr[0] - 65; // 'A' is index 0 and so on.
                        unsigned int ecol = atoi(&subexpr[1]) - 1; // Our index starts at 0 instead of 1
                        subexprValue = allCells[erow][ecol].value;
                    }
                    else
                        subexprValue = atoi(&subexpr[0]);

                    //std::cout  << "pushing number:" << subexprValue << " as a subexpression:****" << subexpr  << "******"<<  std::endl; 
                    rpnStack.push(subexprValue); // just pusch the float value.
            }
        }// end for, we processed the entire expression.
        this->value = rpnStack.top();
    }

  public:
    float value; // The final value of the cell.
    bool computed;

    void initialize(std::string expr, unsigned int row, unsigned int column){
    
        this->computed = false;
        this->row = row;
        this->column = column;
        std::stringstream ss(expr);
        do  {
            std::string elem;
            ss >> elem;
            if (elem[0] != '\0')
                expression.push_back(elem);
            updateSets(elem);
        } while (ss);

    }
    //prints out our cell data structure.
    void printCell() {

        std::cout << "Cell row,col: " << this->row <<  " " << this->column << " Expression: "  ;
        for (std::list<std::string>::iterator it = expression.begin() ; it != expression.end() ; it++)
            std::cout  << *it << " " ;

        std::cout << ": Evaluates ";
        for (std::set<Cell*>::iterator it = evaluates.begin() ; it != evaluates.end() ; it++) {
            Cell* cellptr = *it;
            std::cout << cellptr->row <<  " " << cellptr->column << ", ";
        }
        std::cout << ": Depends on ";
        for (std::set<Cell*>::iterator it = dependsOn.begin() ; it != dependsOn.end() ; it++) {
            Cell* cellptr = *it;
            std::cout << cellptr->row <<  " " << cellptr->column << ", ";
        }

        std::cout << std::endl;
    }

    // The recursive compute call to evaluate the cells one after the other. This is similar to the depth first search.
    void compute() {
        if (!dependsOn.empty())
            return;
        computeRPN();//Evaluate the expression, use appropriate translation as needed via [][] notation.
        this->computed = true;
        //std::cout  << " Value computed for: " <<  this->row << " " <<  this->column << " is "  << this->value  << std::endl ;

        for (std::set<Cell*>::iterator it = evaluates.begin() ; it != evaluates.end() ; it++) {
            Cell* cellptr = *it;
            cellptr->dependsOn.erase(this) ;
            if (cellptr->dependsOn.empty())
                cellptr->compute();
        }
    }

    // The function the computes the RPN notations by using a local stack.

};

// The main function, reads input, initializes the cells. Computes the cells.
int main(int argc, char *argv[]) {
   
    unsigned int width = 0;
    unsigned int height = 0;
    std::string dimensions;
    std::getline(std::cin, dimensions);
    std::stringstream ss(dimensions);
    ss >> width;
    ss >> height;

    allCells = new Cell* [height];
    for (unsigned int i = 0; i < height ; i++)
        allCells[i] = new Cell[width];

    std::string cellString;
    for (unsigned int i = 0; i < height ; i++) {
        for (unsigned int j = 0; j < width ; j++) {
            std::string expr;
            std::getline(std::cin, expr);
            allCells[i][j].initialize(expr, i, j);
        }
    }

    for (unsigned int i = 0; i < height ; i++)
        for (unsigned int j = 0; j < width ; j++) {
            //allCells[i][j].printCell();
            if (allCells[i][j].computed == false)
                allCells[i][j].compute();
        }

    //Check for cyclic dependencies.
    for (unsigned int i = 0; i < height ; i++)
        for (unsigned int j = 0; j < width ; j++) {
            if (allCells[i][j].computed == false) {
                std::cout << "Cyclic dependencies found. Could not compute all the cells" << std::endl;
                exit(1);
            }
            
        }
    
    //Printoout the values of the cells.
    std::cout << width << " " << height << std::endl;
    for (unsigned int i = 0; i < height ; i++)
        for (unsigned int j = 0; j < width ; j++)
            printf("%.5f\n", allCells[i][j].value);
            //std::cout << allCells[i][j].value << std::endl;
            
    //clear and free memory.
    for (unsigned int i = 0; i < height ; i++)
        delete [] allCells[i];
    delete [] allCells;

    return 0;
}
