class Solution {
    public:
        void solveSudoku(vector<vector<char> > &board) {
            solveRecurSudoku(board, 0);
        }
        set<char> getValidItems(const vector<vector<char> > &board, int row, int col) {
            set<char> retSet;
            for (int c = '1'; c <= '9'; c++) {
                if (validItem(board, c, row, col) )
                    retSet.insert(c);
            }
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
                for(int j = boxj*3; i < (boxj + 1)*3; j++)
                    if (board[i][j] == c)
                        return false;
            return true;
        }
        bool solveRecurSudoku(vector<vector<char> >& board, int n) {
                if (n == 81)
                    return true;
                int i = n/9; 
                int j = n - i*9;
            
                set<char> validItems = getValidItems(board, i, j);
                if (validItems.empty())
                    return false;
                for (set<char>::iterator it = validItems.begin(); it != validItems.end(); it++) {
                    vector<vector<char> > newBoard = board;// make a copy
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

int main(int argc, char** argv) {
    vector<vector<char> > board = ["..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."];
    Solution s;
    s.solveSudoku(board); 
}

