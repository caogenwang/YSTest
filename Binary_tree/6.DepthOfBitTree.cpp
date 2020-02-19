struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


//二叉树的深度
int DepthOfTree(TreeNode* root)
{
    if(root)
    {
        return DepthOfTree(root->left)>DepthOfTree(root->right)?DepthOfTree(root->left)+1:DepthOfTree(root->right)+1;
    }
    if( root == nullptr)
    {
        return 0;
    }
}
