struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool SearchBST(TreeNode *T,int key,TreeNode f,TreeNode *p)
{
    if (!T)
    {
        *p = f;
        return false;
    }
    else if (key == T->val)
    {
        p = T;
        return true;
    }
    else if (key < T->val)
    {
        return SearchBST(T->left,key,f,p);
    }
    else
    {
        return SearchBST(T->right,key,f,p);
    }
}