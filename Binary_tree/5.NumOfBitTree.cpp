struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//二叉树节点总数目
int Nodenum(TreeNode* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    else
    {
        return 1+Nodenum(root->left)+Nodenum(root->right);
 
    }
}
