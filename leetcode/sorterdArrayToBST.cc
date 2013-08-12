class Solution {
    TreeNode* recurSol(int start, int end, vector<int> &num) {
        if (start > end)
            return NULL;
        if (start == end)
            return new TreeNode(num[start]);

        if (start + 1 == end) {
            TreeNode* left = new TreeNode(num[start]);
            TreeNode* root = new TreeNode(num[start + 1]);
            root->left = left;
            return root;
        }
        int mid = (start + end)/2;

        TreeNode* left = recurSol(start, mid-1, num);
        TreeNode* right = recurSol(mid+1, end, num);
        TreeNode* root = new TreeNode(num[mid]);
        root->left = left;
        root->right = right;
        return root;
    }
    public:
        TreeNode *sortedArrayToBST(vector<int> &num) {
            return recurSol(0, num.size() - 1, num);
        }
};
