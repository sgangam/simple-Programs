/***
 * Author: Sriharsha Gangam
 * ------------------------
 *
 * Apart from the Hanging Gardens the Babylonians (around 3000-539 b.c.) built the Tower of Babylon as well. The tower was meant to reach the sky, but the project failed because of a confusion of language imposed from much higher above.
 *
 * For the 2638th anniversary a model of the tower will be rebuilt. n different types of blocks are available. Each one of them may be duplicated as many times as you like. Each type has a height y, a width x and a depth z. The blocks are to be stacked one upon eachother so that the resulting tower is as high as possible. Of course the blocks can be rotated as desired before stacking. However for reasons of stability a block can only be stacked upon another if both of its baselines are shorter.
 *
 * Input
 *
 * The number of types of blocks n is located in the first line of each test case. On the subsequent n lines the height yi, the width xi and the depth zi of each type of blocks are given. There are never more than 30 different types available.
 *
 * There are many test cases, which come one by one. Input terminates with n = 0.
 *
 * Output
 *
 * For each test case your program should output one line with the height of the highest possible tower.
 *
 * Example
 *
 * Sample input:
 * 5
 * 31 41 59
 * 26 53 58
 * 97 93 23
 * 84 62 64
 * 33 83 27
 * 1
 * 1 1 1
 * 0
 *
 * Sample output:
 * 342
 * 1
 *
 * */


#include<iostream>
#include<list>
#include<cassert>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class Block {
    public:
        unsigned long int l, b, h;
        Block(unsigned long int l, unsigned long int b, unsigned long int h) {
            this->l = l; this->b = b; this->h = h;
        }
};

class State {
    unsigned long int l, b, h;
    public:
        State(unsigned long int l, unsigned long int b, unsigned long int h) {
            this->l = l; this->b = b; this->h = h;
        }
        unsigned long int getHeight() const {
            return this->h;
        }
        inline void processNextStates (std::list<State> & nextStateList, const std::list <Block> & blockList) const {
            for (std::list<Block>::const_iterator it = blockList.begin(); it != blockList.end(); it++)
                if (it->l > l and it-> b > b) 
                    nextStateList.push_back(State(it->l, it->b, this->h + it->h));
        }
};

class AllBlocks {
    int blockCount;
    unsigned long int maxHeight, maxSide;
    std::list<Block> blockList;
    public:
        AllBlocks (int blocks) {
            maxHeight = 0;
            maxSide = 0;
            this->blockCount = blocks;
            for (int i = 0; i < blocks; i++) {
                unsigned long int x, y, z;
                std::cin >> x; std::cin >> y; std::cin >> z;
                //six rotations.
                blockList.push_back(Block(x, y, z));
                blockList.push_back(Block(y, x, z));
                blockList.push_back(Block(x, z, y));
                blockList.push_back(Block(z, x, y));
                blockList.push_back(Block(y, z, x));
                blockList.push_back(Block(z, y, x));

                maxSide = MAX(maxSide, x); maxSide = MAX(maxSide, y); maxSide = MAX(maxSide, z);
            }
            //runDFS (State(0, 0, 0)) ;
            maxSide += 2;
            runDP();
            std::cout << maxHeight << std::endl;
        }

        void runDP () {
            unsigned long int H[maxSide + 1][maxSide + 1];
            unsigned long int blockHeight[maxSide + 1][maxSide + 1];
            for (unsigned long int i = 0; i <= maxSide ; i++)  {
                H[0][i] = 0;
                H[i][0] = 0;
            }
            for (unsigned long int i = 0; i <= maxSide ; i++)  
                for (unsigned long int j = 0; j <= maxSide ; j++)  
                    blockHeight[i][j] = 0;

            for (std::list<Block>::const_iterator it = blockList.begin(); it != blockList.end(); it++) {
                blockHeight[it->l][it->b] = MAX(blockHeight[it->l][it->b], it->h);
            }

            ///////////////////////////////////////////////
            
            for (unsigned long int i = 1; i <= maxSide; i++) {
                for (unsigned long int j = 1; j <= maxSide ; j++) {
                    //int h = getHeightMatchingBase(i, j);
                    unsigned long int h = blockHeight[i][j];
                    if (h != 0) {
                        H[i][j] = h + H[i-1][j-1];
                        maxHeight = MAX(maxHeight, H[i][j]);
                    }
                    else {
                        H[i][j] = H[i][j-1]; 
                        for (unsigned long int k = 0; k < i; k++){
                            H[i][j] = MAX(H[i][j], H[k][j]); 
                        }
                    }
                }
            }
            

        }
        
        /*
        inline int getHeightMatchingBase(unsigned long int l, unsigned long int b) {
            //int retval = 0;
            unsigned long int maxht = 0;
            for (std::list<Block>::const_iterator it = blockList.begin(); it != blockList.end(); it++)
                if (it->l == l and it->b == b)
                    maxht = MAX(maxht, it->h);
                //else if (it->l < l and it->b < b)
                 ////   smallerBlocks.push_back(*it);
        
            return maxht;
        } 
        */

        void runDFS (const State & s) {
            std::list<State> nextStateList;
            s.processNextStates(nextStateList, blockList);
            if (nextStateList.empty()) {
                unsigned long int h = s.getHeight();
                if (maxHeight < h)
                    maxHeight = h;
                //std::cout << "H:" << maxHeight << std::endl;
                return;
            }
            
            for (std::list<State>::const_iterator it = nextStateList.begin(); it != nextStateList.end(); it++)
                runDFS(*it);

        }


};

int main(int argc, char *argv[]) {
    int blocks = 0;
    std::cin >> blocks;
    while (blocks != 0) {
        AllBlocks ab = AllBlocks(blocks);
        std::cin >> blocks;
    }
}
