#include<vector> 
#include<stack> 
#include<iostream> 

struct TreeNode {
     int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class BinaryTree {
    vector<int> v;
    stack <TreeNode*> stk;
    TreeNode* rootNode;

    void freeTree(TreeNode* node) {
        if (node == NULL) 
            return;
        freeTree(node->left);
        freeTree(node->right);
        freeTree(node);
    }

    public:
    BinaryTree () {
        rootNode = NULL;
    }
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
    void inorderIterative(TreeNode* node) {
        insertLeftNodes(node);
        while (not stk.empty()) {
            TreeNode* curr = stk.top();
            stk.pop();
            v.push_back(curr->val);
            insertLeftNodes(curr->right);  
        }

    }
    void inorderRecursive(TreeNode* root) {
        if (root == NULL)
            return;
        recurCall(root->left);
        v.push_back(root->val);
        recurCall(root->right);
    }
    TreeNode* constructRecursiveInorder(const std::vector<int> & treeVector) {
        if size(treeVector == 0)
                return NULL
        if size(treeVector == 1)
                return new TreeNode(treeVector[0]);
        if size(treeVector == 2) {
                TreeNode* left = new TreeNode(treeVector[0]);
                TreeNode* root = new TreeNode(treeVector[1]);
        }
        int midIndex = len(treeVector)/2;
        vector<int> leftVector(treeVector.begin(), treeVector.begin() + midIndex - 1);
        vector<int> rightVector(treeVector.begin() + midIndex + 1, treeVector.end());
        TreeNode* currRoot = new TreeNode(treeVector[mid]);
        currRoot->left = constructRecursiveInorder(leftVector);
        currRoot->left = constructRecursiveInorder(rightVector);
        return currRoot;
    }
    ~BinaryTree () {
        freeTree(rootNode);
    }
};
int main(int argc, char** argv) {
    return 0;
}
