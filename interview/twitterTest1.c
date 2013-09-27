#include<stdio.h>

int solution(int N) {
    int maxGap = 0;
    int gapBegin = 0; // like a bool
    int gap = 0; // the current gap.
    while (N > 0) {
        //printf("curr gap%d\n", gap );
        int a = N & 1;
        N = N >> 1;
        if (a == 1)  {
            if (!gapBegin) { // begin new gap
                gapBegin = 1;
                gap = 0;
            }
            if (gapBegin && gap > 0) { // closing gap
                if (gap > maxGap)
                    maxGap = gap;
                gap = 0;
                gapBegin = 1;
            }
        }
        else if (a == 0 && gapBegin) {
            gap ++;
        }
    }
    return maxGap;
}

int main() {
    int N = 529;
    N = 1041;
    printf("%d\n", solution(N));
}
