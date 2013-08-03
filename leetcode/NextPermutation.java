/*
 * Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 ->  1,3,2
3,2,1 ->  1,2,3
 1,1,5 ->  1,5,1
*
*/

import java.util.*;

public class NextPermutation {

    public void nextPermutation(int[] num) { 
        if (num.length == 1 || num.length == 0)
            return;
        if (num.length == 2) {
            int temp = num[0];
            num[0] = num[1];
            num[1] = temp;
            return;
        }
        recurNextPermutation(num, 0);
        return;
    }
    private void reverseArray (int[] num, int index) {
        int i = index;
        int j = num.length - 1;
        while (i < j) {
            int temp = num[i];
            num[i] = num[j];
            num[j] = temp;            
            i++;
            j--;
        }
    }

    private boolean maxPermutation(int[] num, int index) {
        for (int i = index; i < num.length - 1 ; i++)
            if (num[i] < num[i+1])
                return false;
        return true;
    }
    private boolean recurNextPermutation(int[] num, int index) {

        if (index == num.length - 2) {
            int temp = num[index];
            num[index] = num[index + 1];
            num[index + 1] = temp;
            if (num[index] > num[index + 1])
                return false;
            else
                return true;
        }

        if (maxPermutation(num, index)) {
            reverseArray(num, index);
            return true;
        }
        if(!recurNextPermutation(num, index + 1))
            return false;
        for (int i = index+1; i < num.length ; i++){
            if (num[i] > num[index]) {
                int temp = num[index];
                num[index] = num[i];
                num[i] = temp;
                break;
            }
        }
        return false;

    }
    public static void main(String[] args){
        NextPermutation s = new NextPermutation();
        //int [] num = {1, 2, 3};
        int [] num = {3, 2, 1};
        s.nextPermutation(num);
        System.out.println(Arrays.toString(num));
    }
}
