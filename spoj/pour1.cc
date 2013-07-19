/***
 * Author: Sriharsha Gangam
 * ------------------------

 * Breadth first search and Depth first search in a graph represented as an adjacency matrix.
 * uring water
 *
 * Problem code: POUR1
 *
 * Given two vessels, one of which can accommodate a litres of water and the other - b litres of water, determine the number of steps required to obtain exactly c litres of water in one of the vessels.
 *
 * At the beginning both vessels are empty. The following operations are counted as 'steps':
 *
 * emptying a vessel,
 * filling a vessel,
 * pouring water from one vessel to the other, without spilling, until one of the vessels is either full or empty.
 * Input
 *
 * An integer t, 1<=t<=100, denoting the number of testcases, followed by t sets of input data, each consisting of three positive integers a, b, c, not larger than 40000, given in separate lines.
 *
 * Output
 *
 * For each set of input data, output the minimum number of steps required to obtain c litres, or -1 if this is impossible.
 *
 * Example
 *
 * Sample input:
 * 2
 * 5
 * 2
 * 3
 * 2
 * 3
 * 4
 * Sample output:
 * 2
 * -1
 *
 * has a fucntion to generate and test graphs of differnt sizes.
 * */

#include<iostream>
#include<queue>
#include<list>
#include<stack>
#include<cassert>
#include<cmath>
#include<algorithm>
#include<tr1/unordered_map>



/***
 * The Graph class. stores a graph as adjacency matrix and has BFS and DFS functions.
 * @member matrix: It contains the graphs stored as an adjacency matrix
 * @member vcount: The vertex count or the maximum number of vertices in the graph. 
 * The vertices can be identified by values 0 to vcount -1. 
 * The edge from vertex i to j is given by matrix[i][j]
***/

class State {
        int maxa, maxb, a, b;
    public:
        friend std::ostream& operator<< (std::ostream &out, const State & s);
        State(int maxa, int maxb) {
            this->maxa = maxa;
            this->maxb = maxb;
            a = b = 0;
        }
        State(const State &s) {
            this->maxa = s.maxa;
            this->maxb = s.maxb;
            this->a = s.a;
            this->b = s.b;
        }
        bool operator== (const State & s) const {
            return (this->maxa == s.maxa && this->maxb == s.maxb && this->a == s.a && this->b == s.b);
        }
        bool operator!= (const State &s ) const {
            return !(*this == s);
        }
        std::size_t getHash() const { 
            //return (std::tr1::hash<int>()(maxa)) ^ (std::tr1::hash<int>()(maxb) << 1) ^ (std::tr1::hash<int>()(a) << 2) ^ (std::tr1::hash<int>()(b) << 3);
            return (std::tr1::hash<int>()(a) ) ^ (std::tr1::hash<int>()(b) << 1);
        }

        bool endSearch(int c) const {
            if (c == a || c == b)
                return true;
            else
                return false;
        }
        void processNextStates (std::list<State> & nextStateList) const {
            // Empty A
            if (a != 0) {
                State s(*this);
                s.a = 0;
                nextStateList.push_back(s);
            }
            // Empty B
            if (b != 0) {
                State s(*this);
                s.b = 0;
                nextStateList.push_back(s);
            }
            // Fill A
            if (a < maxa) {
                State s(*this);
                s.a = maxa;
                nextStateList.push_back(s);
            }
            // Fill B
            if (b < maxb) {
                State s(*this);
                s.b = maxb;
                nextStateList.push_back(s);
            }
            // Pour A to  B
            if (a > 0 && b < maxb) {
                State s(*this);
                int minval = std::min(a, maxb - b);
                s.a = a - minval;
                s.b = b + minval;
                nextStateList.push_back(s);
            }
            // Pour B to A
            if (b > 0 && a < maxa) {
                State s(*this);
                int minval = std::min(b, maxa - a);
                s.a = a + minval;
                s.b = b - minval;
                nextStateList.push_back(s);
            }
        }
};

std::ostream& operator<< (std::ostream & out, const State & s) {
    out << "(" << s.a << ", " << s.b <<  ")";
    return out;
}
/*
class KeyEqual {
    public:
        bool operator()(const State& s1, const State& s2) const{
            return (s1 == s2);
        }
};
*/
class KeyHash {
    public:
        std::size_t operator()(const State& s) const {
            return s.getHash(); 
        }
};

/***
 * Given a map of the path taken for the BFS or DFS search. This function prints this path.
 * @param src: The vertex indicating the start of the search process
 * @param dst: The vertex indicating the end of the search process
***/
void printSearchPath(const std::tr1::unordered_map <State, State, KeyHash> & parent, State src, State dst) {
        State curr = dst;
        std::cout << "Start State:" << src << " End State: " << dst << std::endl;
        while (curr != src) {
            std::cout << curr << " <- ";
            std::tr1::unordered_map<State, State, KeyHash>::const_iterator it = parent.find(curr);
            curr = it->second;
        }
        std::cout << curr << std::endl;
}

/***
 * Follows a breadth first search traversal. 
***/

int pour1 (int maxa, int maxb, int c) {
    if (maxb > maxa) { //swap a and b
        maxa = maxa ^ maxb; maxb = maxa ^ maxb; maxa = maxa ^ maxb;
    }
    if (c > maxa)
        return -1;

    std::queue <State> vqueue; // A queue of vertex ids.
    std::tr1::unordered_map<State, State, KeyHash> parentMap; // A path to the parent.
    std::tr1::unordered_map<State, int, KeyHash> stepsMap; // steps take to reach that state

    State initState(maxa, maxb);
    vqueue.push(initState);
    std::pair<State, int> stepPair (initState, 0);
    stepsMap.insert(stepPair);
    std::pair<State, State> parentPair (initState, initState);
    parentMap.insert(parentPair);
    int steps = -1;
    while (!vqueue.empty()) {
        State front = vqueue.front();
        //std::cout << "Front of Queue is:" << front << std::endl;
        vqueue.pop();
        //found the path from src to dst.
        if (front.endSearch(c)) {
            steps = stepsMap[front]; 
            //printSearchPath (parentMap, initState, front);
            break;
        }
        std::list <State> nextStateList;
        front.processNextStates(nextStateList);
        for (std::list<State>::const_iterator it = nextStateList.begin(); it != nextStateList.end(); ++it) {
            State nextState = *it;
            std::tr1::unordered_map<State, State, KeyHash>::const_iterator it = parentMap.find(nextState);
            if (it == parentMap.end()) {
                std::pair<State, State> mypair (nextState, front);
                parentMap.insert(mypair);
                stepsMap[nextState] = 1 + stepsMap[front];
                vqueue.push(nextState);
            }
        }
    }

    return steps;
}

int main(int argc, char *argv[]) {
    int testCount = 0;
    int maxa = 0; int maxb = 0; int c = 0;
    std::cin >> testCount;
    for (int i = 0; i < testCount ; i++) {
        std::cin >> maxa;
        std::cin >> maxb;
        std::cin >> c;
        std::cout << pour1(maxa, maxb, c) << std::endl;
    }
    return 0;
}
