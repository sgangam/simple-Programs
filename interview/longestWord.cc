/*
 * Author: Sriharsha Gangam
 * www.cs.purdue.edu/homes/sgangam/
 *
 * Compiling: g++ longestWord.cc
 * Usage: ./a.out < inputFile.txt
 *
 * Notes: The program can be further optimized by combining the search and insert phase.
 */
#include<iostream>
#include<string>
#include<cassert>
#include<queue>
#include<list>


#define ALPH_SIZE 26 // correspoinding to 26 letters of the alphabet
/*
 * Node is a data Structure for a trie or prefex tree
 * @member head: is the static Node* member storing an invalid '0' character.
 * @member charVal: stores the character value of the current node. This is used only for priting purposes and is not used in the program
 * @member nodeArray: For each of the 26 characters, we have an element in the array. char 'a' is index 0, 'b' is index 1 and so on.
 * @member validWord: Indicates if the current char or node in the trie marks the end of the word.
 */
using namespace std;
class Node {
    Node* nodeArray[ALPH_SIZE];
    static Node* head;
    char charVal;
    bool validWord;
  public:
    Node(char c): charVal(c), validWord(false){
        if (c == '0')
            head = this;
        for (int i = 0; i < ALPH_SIZE; i++)
            nodeArray[i] = NULL;
    };
    ~Node(){
        for (int i = 0; i < ALPH_SIZE; i++)
            if (nodeArray[i] != NULL)
                delete nodeArray[i];
    }
    /*
     * This is a recursive function. Takes a string (char array) s and and
     * index. Checks if the substring starting at given index is composed of
     * other smaller strings in the trie.  Since we insert smaller length
     * strings into the trie before inserting larger ones, we should be able to
     * accurately detect all strings that can be composed of other smaller
     * strings.  
     * @argument s: The string being tested 
     * @argument index: The * index of the string from which to start the test.
     */
    static bool substringsPresent(const string & s, unsigned int index = 0){
        Node* currNode = head;
        for (; index < s.length(); index++) {
            int arrIndex = s[index] - 'a'; 
            Node* nodePtr = currNode->nodeArray[arrIndex];
            if (nodePtr == NULL) {
                return false;
            }
            else if (nodePtr->validWord and nodePtr->substringsPresent(s, index+1))
                return true;
            currNode = nodePtr;
        }
        if (currNode->validWord)
            return true;
        else
            return false;
    }

    /*
     * Takes a string s and inserts it in our trie.
     * @param s: The input string.
     */
    static void insertString(const string & s){
        unsigned int index = 0;
        Node* currNode = head;
        for (; index < s.length(); index++) {
            int arrIndex = s[index] - 'a'; 
            Node* nodePtr = currNode->nodeArray[arrIndex];
            if (nodePtr == NULL) {
                currNode->nodeArray[arrIndex] = new Node(s[index]);        
            }
            currNode = currNode->nodeArray[arrIndex];
        }
        currNode->validWord = true;
    }
    /*
     * The function the print the trie. It is not required by our program but it can be used for debuggin purposes.
     * It starts from the head node and performs a breadth first search (BFS).
     */
    static void printTrie() {
        queue<const Node*> nq;
        nq.push(head);
        nq.push(NULL);
        while(not nq.empty()) {
           const Node* currTop = nq.front();
           nq.pop();
           if (currTop != NULL) {
               for (int i = 0; i < ALPH_SIZE; i++){
                   const Node* nodePtr = currTop->nodeArray[i];
                    if (nodePtr != NULL) {
                        cout << nodePtr->charVal ;
                        (nodePtr->validWord == true) ? (cout << "* " ): (cout << " ");
                        nq.push(nodePtr) ;
                    }
                }
            }
            else {
                cout << endl ;
                if (not nq.empty())
                    nq.push(NULL);
            }
        }
    }
};
Node* Node::head;

/*
 * A function that takes two strings and returs if the first string has a shorter length than the second string.
 * This is used by list.sort() to sort a list of string in the decreasing order of their sizes.
 * @param s1: First string
 * @param s2: Second string
 */
bool compareLength(const string & s1, const string& s2){
    if (s1.length() < s2.length())
        return true;
    else
        return false;
}

int main(int argc, char** argv) {
    string s; list<string> strList;
    while (cin >> s) {// Read all input strings and save them in a list.
       strList.push_back(s);
    }
    /* sort the strings in the list on the decreasing order of length. By
     * adding words with smaller length first, we ensure that all composable
     * words are detected.
     */
    strList.sort(compareLength);
    Node head('0'); // Initialize the head node with a char '0'.

    string longestString = "", secondlongestString = ""; // keep track of the longest and second longest string that can be composed of other smaller strings.
    int composedWords = 0; // The total number of words than can be created by other smaller words.

    for(list<string>::iterator it = strList.begin(); it != strList.end(); it++) {
        string& currString = *it;
        if (head.substringsPresent(currString)) { // check if the current string can be composed/created with other smaller strings that we inserted previously.
            composedWords++;
            if (currString.length() > longestString.length()) {
                secondlongestString = longestString;
                longestString = currString;
            }
            else if (currString.length() > secondlongestString.length())
                secondlongestString = *it;
        }
        head.insertString(currString); // Insert the current string into the trie.
        //head.printTrie();
    }   
    cout << "Longest String:"  << longestString<< "  Second Longest String:"<< secondlongestString << "  Words composed of other smaller words:" << composedWords << endl;
    return 0;
}
