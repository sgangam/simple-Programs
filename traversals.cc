#include<vector> 
#include<stack> 
#include<iostream> 
/******
 *
 * In order pre order  travels are well know in binary trees using recursion.
 * This source provides iterative solutions for in order and pre order traversal.
 * The code also has functions to convert a vector to a binary tree using recursion.
 *
 * TODO: Pretty prin the binary tree.
 * Author: Sriharsha Gangam
 *
 *///
void printVector(const std::vector<int> & v) {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
        std::cout << *it << " " ;

    std::cout << std::endl;

}

class TreeNode {
    public:
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class BinaryTree {
    std::vector<int> v;
    std::stack <TreeNode*> stk;
    TreeNode* rootNode;

    void freeTree(TreeNode* node) {
        if (node == NULL) 
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

    TreeNode* constructRecursiveInorder(const std::vector<int> & treeVector) {
        if (treeVector.empty())
                return NULL;
        if (treeVector.size() == 1)
                return (new TreeNode(treeVector[0]));
        if (treeVector.size() == 2) {
                TreeNode* newLeft = new TreeNode(treeVector[0]);
                TreeNode* newRoot = new TreeNode(treeVector[1]);
                newRoot->left = newLeft;
                return newRoot;
        }
        int midIndex = treeVector.size()/2;
        std::vector<int> leftVector(treeVector.begin(), treeVector.begin() + midIndex);
        std::vector<int> rightVector(treeVector.begin() + midIndex + 1, treeVector.end());
        //printVector(leftVector);
        //printVector(rightVector);
        TreeNode* currRoot = new TreeNode(treeVector[midIndex]);
        currRoot->left = constructRecursiveInorder(leftVector);
        currRoot->right = constructRecursiveInorder(rightVector);
        return currRoot;
    }

    public:
    void insertRightNodes(TreeNode* node) {
        while (node != NULL) {
            stk.push(node);
            node = node->right;
        }
    }
    void insertLeftNodes(TreeNode* node) {
        while (node != NULL) {
            stk.push(node);
            node = node->left;
        }
    }
    void iterativeInorder() {
        v.clear();
        insertLeftNodes(rootNode);
        while (not stk.empty()) {
            TreeNode* curr = stk.top();
            stk.pop();
            v.push_back(curr->val);
            insertLeftNodes(curr->right);  
        }
    }
    /****
     * This is a simple depth first search
     */
    void iterativePreorder() {
        v.clear();
        stk.push(rootNode);  
        while (not stk.empty()) {
            TreeNode* curr = stk.top();
            stk.pop();
            v.push_back(curr->val);
            if (curr->right != NULL)
                stk.push(curr->right);  
            if (curr->left != NULL)
                stk.push(curr->left);  
        }
    }

    BinaryTree () {
        rootNode = NULL;
    }
    std::vector<int> getVectorRepresentation() {
        return v;
    }
    void simpleInorder() {
        v.clear();
        inorderRecursive(rootNode); 
    }
    void simplePreorder() {
        v.clear();
        preorderRecursive(rootNode); 
    }
    void simplePostorder() {
        v.clear();
        postorderRecursive(rootNode); 
    }

    void inorderRecursive(TreeNode* root) {
        if (root == NULL)
            return;
        inorderRecursive(root->left);
        v.push_back(root->val);
        inorderRecursive(root->right);
    }

    void preorderRecursive(TreeNode* root) {
        if (root == NULL)
            return;
        v.push_back(root->val);
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }
    void postorderRecursive(TreeNode* root) {
        if (root == NULL)
            return;
        postorderRecursive(root->left);
        postorderRecursive(root->right);
        v.push_back(root->val);
    }

    void constructInorder(const std::vector<int> & treeVector) {
        rootNode = constructRecursiveInorder(treeVector);
    }


    ~BinaryTree () {
        freeTree(rootNode);
    }
};

int main(int argc, char** argv) {
    std::vector<int> v;
    for(int i = 0; i < 11; i++) 
        v.push_back(i+100);
    printVector(v);
    BinaryTree bt; 
    bt.constructInorder(v);
    std::cout << "-----------------------------------------------" <<std::endl;

    bt.simpleInorder();
    printVector(bt.getVectorRepresentation());
    bt.iterativeInorder();
    printVector(bt.getVectorRepresentation());
    std::cout << std::endl;

    bt.simplePreorder();
    printVector(bt.getVectorRepresentation());
    bt.iterativePreorder();
    printVector(bt.getVectorRepresentation());
    std::cout << std::endl;

    bt.simplePostorder();
    printVector(bt.getVectorRepresentation());
    //bt.iterativePostorder();
    //printVector(bt.getVectorRepresentation());
    std::cout << std::endl;

    return 0;
}
