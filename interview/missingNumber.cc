#include<iostream>

using namespace std;
int findMissing(int a[], int len) {
    int left = 0;
    int right = len - 1;
    int offset = a[0];
    while(left < right) {
        int mid = (left + right)/2;
        if (a[mid] == offset + mid) 
            left = mid+1;
        else {
            right = mid;
        }
    }
    return a[left] - 1;

}


int main(int argc, char** argv) {

    int a[] = {1,2,3,4,6,7,8};
    cout << "Missing:" << findMissing(a, 7) << endl;
    int b[] = {11,12,13,14,15,16,18};
    cout << "Missing:" << findMissing(b, 7) << endl;
    int c[] = {21,22,23,24,25,26,27, 28, 29, 30, 31, 33, 34};
    cout << "Missing:" << findMissing(c, 13) << endl;
    int d[] = {21,22,23,24,25,26,27, 28, 29, 30, 31, 32, 34, 35};
    cout << "Missing:" << findMissing(d, 14) << endl;
}

