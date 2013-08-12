/*
 * Surrounded Regions
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region .

For example,

    X X X X
    X O O X
    X X O X
    X O X X
    After running your function, the board should be:

    X X X X
    X X X X
    X X X X
    X O X X

author: Sriharsha Gangam
**/

class Solution {
    void initializeBoundary(vector<vector<char>> &board) {
        int rows = board.size();
        int cols = board[0].size();
            for (int i = 0; i < cols ; i++) {
                if (board[0][i] == 'O') 
                    board[0][i] = '*';
                if (rows - 1 > 0 and board[rows - 1][i] == 'O') 
                    board[rows - 1][i] = '*';
            }
            for (int i = 1; i < rows - 1; i++){
                if (board[i][0] == 'O')
                    board[i][0] = '*';
                
                if (cols - 1 > 0 and board[i][cols - 1] == 'O') 
                    board[i][cols - 1] = '*';
            }

    }
    bool neighborStart(vector<vector<char>> &board, int r, int c) {
        if (board[r-1][c] == '*' or board[r+1][c] == '*' or board[r][c-1] == '*' or board[r][c+1] == '*')
            return true;
        else
            return false;
    }


    void iterConvertStar (vector<vector<char>> &board) {
        int rows = board.size();
        int cols = board[0].size();

        initializeBoundary(board);
        for (int count = 0 ; count < max(rows, cols) ; count++){
            for (int i = 1; i < rows - 1; i++){
                for (int j = 1; j < cols - 1; j++){
                    if (board[i][j] == 'O' and neighborStart(board, i, j)) 
                        board[i][j] = '*';
                }
            }
        }
    }

    public:
        void solve(vector<vector<char>> &board) {
            int rows = board.size();
            if (rows == 0)
                return;
            int cols = board[0].size();
            iterConvertStar(board);
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    if (board[i][j] == '*')
                        board[i][j] = 'O';
                    else if (board[i][j] == 'O')
                        board[i][j] = 'X';
                }
            }
        }
        void solve1(vector<vector<char>> &board) {
            int rows = board.size();
            if (rows == 0)
                return;
            int cols = board[0].size();
            //go across the boundary.
            for (int i = 0; i < cols ; i++) {
                if (board[0][i] == 'O') {
                    convertStar(board, 0, i);
                }
                if (rows - 1 > 0 and board[rows - 1][i] == 'O') {
                    convertStar(board, rows - 1, i);
                }
            }
            for (int i = 1; i < rows - 1; i++){
                if (board[i][0] == 'O') {
                    convertStar(board, i, 0);
                }
                if (cols - 1 > 0 and board[i][cols - 1] == 'O') {
                    convertStar(board, i, cols - 1);
                }
            }
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    if (board[i][j] == '*')
                        board[i][j] = 'O';
                    else if (board[i][j] == 'O')
                        board[i][j] = 'X';
                }
            }
        }
};
