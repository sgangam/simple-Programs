// Comparing from Right to left.

#include<string>
#include<iostream>
#include<cassert>

bool interleaving (std::string x, std::string y, std::string z) {
    if (z.length() != x.length() + y.length())
        return false;

    bool A[x.length() + 1][y.length() + 1][z.length() + 1];
    for (int p = 0; p <= x.length() ; p++) 
        for (int q = 0; q <= y.length() ; q++) 
            for (int r = 0 ; r <= z.length(); r++ ) 
                A[p][q][r] = false;

    for (int p = 1; p <= x.length(); p++) 
        if (x.substr(0, p)  == z.substr(0, p))
            A[p][0][p] = true;

    for (int q = 1; q <= y.length(); q++) 
        if (y.substr(0, q) == z.substr(0, q)) 
            A[0][q][q] = true;


    A[0][0][0] = true;


    for (int p = 1; p <= x.length() ; p++) {
        for (int q = 1; q <= y.length() ; q++) {
            for (int r = 1 ; r <= z.length(); r++ ) {
                    int i = p - 1; int j = q - 1; int k = r - 1;
                    if (y[j] == z[k] and x[i] == z[k])
                        A[p][q][r] = A[p][q-1][r-1] or A[p-1][q][r-1];

                    if (y[j] == z[k])
                        A[p][q][r] = A[p][q-1][r-1];

                    else if (x[i] == z[k])
                        A[p][q][r] = A[p-1][q][r-1];
                    else 
                        A[p][q][r] = false;
                    
                    //std::cout << "pqr" << " " << p << " " << q << " " << r << " " ;
                    //std::cout << "x:" << " " << x.substr(0, p) << " " << "y:" << " " << y.substr(0,q)  << " " <<"z:" << " " << z.substr(0,r) << " result " << A[p][q][r] << std::endl ;
            }
        }
    }

    return A[x.length()][y.length()][z.length()];
}

int main (int argc, char** argv) {
    assert(interleaving("","",""));
    assert(interleaving("a","","a"));
    assert(interleaving("b","","b"));
    assert(interleaving("a","p","ap"));
    assert(interleaving("a","p","pa"));
    assert(interleaving("ab","p","abp"));
    assert(interleaving("ab","p","apb"));
    assert(interleaving("ab","p","pab"));
    assert(interleaving("a","pq","apq"));
    assert(interleaving("ab","pq","abpq"));
    assert(interleaving("abc","pqr","abcpqr"));
    assert(not interleaving("abcc","pqr","cabcpqr"));
    assert(not interleaving("aas","pqr","abcpqr"));

    std::string s1 = "abcd";
    std::string s2 = "pqrs";
    std::string s3 = "apbqcdrs";
    assert(interleaving (s1, s2, s3));
}
