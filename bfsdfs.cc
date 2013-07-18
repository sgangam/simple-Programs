/***
 * Author: Sriharsha Gangam
 * ------------------------
 * Breadth first search and Depth first search in a graph represented as an adjacency matrix.
 * has a fucntion to generate and test graphs of differnt sizes.

 * */

#include<iostream>
#include<queue>
#include<stack>
#include<cassert>
#include<cmath>
#include <unordered_map>

/***
 * A fucnction to generate undirected deterministic graph with configurable sparcity.
 * @param vcount: The number of vertices in the graph
 * @param ost: The output stream to write the graph (file or standard output)
 */

void generateGraph (int vcount, std::ostream & ost) {
    ost << vcount << std::endl;
    int sparcity = 3;
    for (int i = 0; i < vcount; i++) {
        for (int j = 0; j < vcount ; j++)
            if ( ((1 + (i * j)) % (i + j + 2)) % sparcity == 0)
                ost << "1 "; // some undirected graph.
            else
                ost << "0 "; // some undirected graph.
        ost << std::endl;
    }
}

/***
 * The Graph class. stores a graph as adjacency matrix and has BFS and DFS functions.
 * @member matrix: It contains the graphs stored as an adjacency matrix
 * @member vcount: The vertex count or the maximum number of vertices in the graph. 
 * The vertices can be identified by values 0 to vcount -1. 
 * The edge from vertex i to j is given by matrix[i][j]
***/

class Graph {

    // Generates a graph of vcount vertices.
    int **matrix;
    int vcount;
    void printSearchPath(const std::unordered_map <int, int> & parent, int src, int dst) const;
    
    public:
    
    void bfs(int src, int des) const;// provides the shortest number of hops to get from src to des.
    void dfs(int src, int des) const;

    Graph(std::istream & ist) {
        ist >> vcount;
        int rows = vcount; int cols = vcount;
        //allocate memory
        matrix = new int* [rows];
        for (int i = 0; i < vcount; i++) 
            matrix[i] = new int [cols];

        for (int i = 0; i < vcount; i++) 
            for (int j = 0; j < vcount; j++)
                ist >> matrix[i][j];
    }
    //clear and free memory.
    ~Graph () {
        int rows = vcount; 
        for (int i = 0; i < rows ; i++)
            delete [] matrix[i];
        delete [] matrix;
    }

    // Prints the graphs
    void print() const {
        std::cout << vcount << std::endl;
        for (int i = 0; i < vcount; i++) {
            for (int j = 0; j < vcount; j++)
                std::cout << matrix[i][j] << " " ;
            std::cout << std::endl;
        }
    }

};
/***
 * Follows a depth first search traversal. from the src vertex to the destination vertex
 * @param src: The vertex indicating the start of the search process
 * @param dst: The vertex indicating the end of the search process
***/

void Graph::dfs (int src, int dst) const{
    if (!(src >= 0 && dst >= 0 && src < vcount && dst < vcount)) {
        std::cout << "src:" << src <<  " and dst " << dst << " must take values between 0 and " << vcount << std::endl;
        assert(false);
    }

    std::stack <int> vstack; // A stack of vertex ids.
    std::unordered_map<int, int> parent; // A path to the parent.
    vstack.push(src);
    bool found = false;
    while (!vstack.empty()) {
        int front = vstack.top();
        vstack.pop();

        //found the path from src to dst.
        if (front == dst) {
            found = true;
            break;
        }

        for (int i = 0; i < vcount; i++) {
            if (matrix[front][i] != 0 && i != front) {
                std::unordered_map<int, int>::const_iterator it = parent.find(i);
                if (it == parent.end()) {
                    std::pair<int, int> mypair (i, front);
                    parent.insert(mypair);
                    vstack.push(i);
                }
            }
        }
    }
    if (!found)
        std::cout << "No path from " << src << " to " << dst << std::endl;
    else {    
        std::cout << "Depth First Search (DFS) path from " << src << " to " << dst << std::endl;
        printSearchPath(parent, src, dst);
    }
}

/***
 * Given a map of the path taken for the BFS or DFS search. This function prints this path.
 * @param src: The vertex indicating the start of the search process
 * @param dst: The vertex indicating the end of the search process
***/

void Graph::printSearchPath(const std::unordered_map <int, int> & parent, int src, int dst) const {
        int curr = dst;
        while (curr != src) {
            std::cout << curr << " <- ";
            std::unordered_map<int, int>::const_iterator it = parent.find(curr);
            curr = it->second;
        }
        std::cout << curr << std::endl;
}

/***
 * Follows a breadth first search traversal. from the src vertex to the destination vertex
 * @param src: The vertex indicating the start of the search process
 * @param dst: The vertex indicating the end of the search process
***/

void Graph::bfs (int src, int dst) const {
    if (!(src >= 0 && dst >= 0 && src < vcount && dst < vcount)) {
        std::cout << "src:" << src <<  " and dst " << dst << " must take values between 0 and " << vcount << std::endl;
        assert(false);
    }

    std::queue <int> vqueue; // A queue of vertex ids.
    std::unordered_map<int, int> parent; // A path to the parent.
    vqueue.push(src);
    bool found = false;
    while (!vqueue.empty()) {
        int front = vqueue.front();
        vqueue.pop();
        //found the path from src to dst.
        if (front == dst) {
            found = true;
            break;
        }

        for (int i = 0; i < vcount; i++) {
            if (matrix[front][i] != 0 && i != front) {
                std::unordered_map<int, int>::const_iterator it = parent.find(i);
                if (it == parent.end()) {
                    std::pair<int, int> mypair (i, front);
                    parent.insert(mypair);
                    vqueue.push(i);
                }
            }
        }
    }
    if (!found)
        std::cout << "No path from " << src << " to " << dst << std::endl;
    else {
        std::cout << "Breadth First Search (BFS) path from " << src << " to " << dst << std::endl;
        printSearchPath(parent, src, dst);
    }
}


/***
 * Has different tests which compute BFS and DFS for different sources and destinations in a given graph.
***/

void runTests(const Graph & g) {
    g.bfs(9,9);
    g.dfs(9,9);

    g.bfs(9,0);
    g.dfs(9,0);

    g.bfs(8,9);
    g.dfs(8,9);

    g.bfs(3,9);
    g.dfs(3,9);

    g.bfs(13,19);
    g.dfs(13,19);

    g.bfs(45,35);
    g.dfs(45,35);

    g.bfs(22,3);
    g.dfs(22,3);

    g.bfs(9,28);
    g.dfs(9,28);
}

int main(int argc, char *argv[]) {
    //generateGraph(50, std::cout);
    Graph g(std::cin);
    g.print();
    runTests(g);
    return 0;
}
