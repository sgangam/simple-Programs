/*
 * Author: Sriharsha Gangam
 *
 * Solves the sudoku problem from leetcode.com Given a sudoku board as an 9 x 9
 * vector of vector of chars, with unfilled box as '.' and filled boxes as '1'
 * to '9'. Solves the problem and places the answer in the same board.
 *
 * Ideally we want to define a Board class. This solution is tested with the Online Judge at leetcode.com
 */

#include<iostream>
#include<set>
#include<vector>
#include<string>
using namespace std;


class Solution {
    public:
        void solveSudoku(vector<vector<char> > &board) {
            solveRecurSudoku(board, 0);
        }
        set<char> getValidItems(const vector<vector<char> > &board, int row, int col) {
            set<char> retSet;
            for (int c = '1'; c <= '9'; c++) {
                if (validItem(board, c, row, col) ) {
                    retSet.insert(char(c));
                }
            }
            return retSet;
        }
        bool validItem(const vector<vector<char> > &board, char c, int row, int col) {
            for(int i = 0; i < 9; i++)
                if (board[row][i] == c)
                    return false;
            for(int i = 0; i < 9; i++)
                if (board[i][col] == c)
                    return false;
            int boxi = row/3; int boxj = col/3;
            for(int i = boxi*3; i < (boxi + 1)*3; i++)
                for(int j = boxj*3; j < (boxj + 1)*3; j++)
                    if (board[i][j] == c)
                        return false;
            return true;
        }
        bool solveRecurSudoku(vector<vector<char> >& board, int n) {
                if (n == 81)
                    return true;
                int i = n/9; int j = n - i*9;
                if ( board[i][j] != '.')
                    return solveRecurSudoku(board, n+1);
            
                set<char> validItems = getValidItems(board, i, j);
                if (validItems.empty())
                    return false;

                vector<vector<char> > newBoard = board;// make a copy
                for (set<char>::iterator it = validItems.begin(); it != validItems.end(); it++) {
                    newBoard[i][j] = *it;
                    bool retval = solveRecurSudoku(newBoard, n+1);
                    if (retval == true) {
                        board = newBoard;// deep copy
                        return true;
                    }
                }
                return false;// cannot solve sudoku
        }
};

vector<vector<char> >  convert(const char  matrix[9][10]) {
    vector<vector<char> > board ;
    board.resize(9);
    for (int i = 0; i < 9; i++) {
        board[i].resize(9);
        for (int j = 0; j < 9; j++) {
            board[i][j] = matrix[i][j];
            //cout << board[i][j] << " * " ;
        }
    }
    return board;
}

int main(int argc, char** argv) {
    char matrix[9][10]= {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
    vector<vector<char> > board = convert(matrix);
    Solution s;
    s.solveSudoku(board); 
}

