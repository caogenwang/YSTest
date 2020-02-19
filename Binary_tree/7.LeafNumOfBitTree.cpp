struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int Leafnum(TreeNode * root)
{
    if(!root)
    {
        return 0;
    }
    else if(  (root->left == nullptr) && (root->right == nullptr) )
    {
        return 1;
    }
    else
    {
        return  (Leafnum(root->left) + Leafnum(root->right)) ;
    }
}
