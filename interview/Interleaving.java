/*************************************************************************
*  Author: Sriharsha Gangam
*
*  Compilation:  javac Interleaving.java
*  Execution:    java Interleaving
*
*  Interleaving: Takes three strings and tests if the third string is
*  an interleaving of the first two strings.
*
*************************************************************************/



public class Interleaving {
    /*
     * Tests if String z is an interleaving of x and y.
     * A string z interleaves x and y if (1) all the characters of
     * x and y are present in z  (2) all characters of z either belong
     * to x or y and, (3) the order of characters in z follow the
     * same order in their origina strings x and y.
     * Example: "abpcqrd"  is an interleaving of string "abcd" and "pqr"
     *
     * Gloal: Given three strings, the function determines if one is an
     * interleaving of the other two.
     */
    public static boolean interleaving (String x, String y, String z) {
        int xlen = x.length(); int ylen = y.length(); int zlen = z.length();

        boolean [][][] interleavingState = new boolean [xlen + 1][ylen + 1][zlen + 1]; 
        interleavingState[0][0][0] = true;
        interleavingState[1][0][0] = interleavingState[0][1][0] = interleavingState[0][0][1] = interleavingState[1][1][0] = interleavingState[1][1][1] = false;
        

        System.out.println("In Interleaving");
        return true;
    }

    public static void main (String[] args){

        assert interleaving("a","","a");
        assert interleaving("b","","b");
        assert interleaving("a","p","ap");
        assert interleaving("ab","p","abp");
        assert interleaving("ab","p","apb");
        assert interleaving("ab","p","pab");
        assert interleaving("a","pq","apq");
        assert interleaving("ab","pq","abpq");
        assert interleaving("abc","pqr","abcpqr");
        String s1 = "abcd";
        String s2 = "pqrs";
        String s3 = "apbqcdrs";
        interleaving (s1, s2, s3);
        System.out.println("In main");
    }
}
