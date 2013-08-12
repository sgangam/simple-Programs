/*
 * Author: Sriharsha Gangam

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
    Given the following matrix:

    [
     [ 1, 2, 3 ],
      [ 4, 5, 6 ],
       [ 7, 8, 9 ]
       ]
       You should return [1,2,3,6,9,8,7,4,5].
*/
import java.util.*;



public class SpiralMatrix {
    public ArrayList<Integer> spiralOrder(int[][] matrix) {

        if(matrix.length == 0)
            return new ArrayList<Integer>();

        return recurSpiral(matrix, 0, matrix.length - 1, 0, matrix[0].length - 1);

    }
    ArrayList<Integer> recurSpiral(int[][] matrix, int startRow, 
            int endRow, int startCol, int endCol) {

        ArrayList<Integer> ret = new ArrayList<Integer>();                    

        if (startRow > endRow || startCol > endCol)
            return ret;

        for(int col = startCol; col <= endCol; col++)
            ret.add(matrix[startRow][col]);

        for (int row = startRow + 1; row <= endRow; row++)
            ret.add(matrix[row][endCol]);

        for(int col = endCol - 1; endRow > startRow && col >= startCol; col--)
            ret.add(matrix[endRow][col]);

        for (int row = endRow - 1; startCol < endCol && row >= startRow + 1; row--)
            ret.add(matrix[row][startCol]);

        ArrayList<Integer> sub = recurSpiral(matrix, startRow + 1, endRow - 1, startCol + 1, endCol - 1);
        ret.addAll(sub);
        return ret;
    }


    public static void main(String args[]) {
        SpiralMatrix s = new SpiralMatrix();
        int [][] matrix = {{2, 3}};
        ArrayList<Integer> ret = s.spiralOrder(matrix);
        System.out.println(Arrays.toString((ret.toArray(new Integer[ret.size()])))   );
    }
}
