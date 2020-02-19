struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
extern bool SearchBST(TreeNode *T,int key,TreeNode f,TreeNode *p);
bool InsertBST(TreeNode*T,int key)
{
    TreeNode *p,*s;

    if (!SearchBST(T,key,0,p))
    {
        s = new TreeNode(key);
        if (!p)
        {
            T = s;
        }
        else if(key < p->val)
        {
            p->left = s;
        }
        else
        {
            p->right = s;
        }
    }
    else
    {
        return false;
    }
    
    
}