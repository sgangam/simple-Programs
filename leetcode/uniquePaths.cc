class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            int rows =  obstacleGrid.size();
            int cols =  obstacleGrid[0].size();
            if (obstacleGrid[0][0] == 1)
                return 0;
            int uniquePaths[rows][cols];
            uniquePaths[0][0] = 1;
            for (int i = 1; i < rows; i++)
                if (obstacleGrid[i][0] == 0)
                    uniquePaths[i][0] = uniquePaths[i-1][0];
                else
                    uniquePaths[i][0] = 0;

            for (int i = 1; i < cols; i++)
                if (obstacleGrid[0][i] == 0)
                    uniquePaths[0][i] = uniquePaths[0][i-1];
                else
                    uniquePaths[0][i] = 0;

            for (int i = 1; i < rows; i++)
                for (int j = 1; j < cols; j++)
                    if (obstacleGrid[i][j] == 0)
                        uniquePaths[i][j] = uniquePaths[i-1][j] + uniquePaths[i][j-1];
                    else
                        uniquePaths[i][j] = 0;

            return uniquePaths[rows - 1][cols - 1];
        }
};
