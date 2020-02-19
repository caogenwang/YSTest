#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <map>
#include <list>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *create(vector<int> &arrary)
{
    TreeNode *root = new TreeNode(arrary[0]);
    for (int i = 1; i < arrary.size(); i++)
    {
        TreeNode *node = new TreeNode(arrary[i]);
        Insert(root,node);
    }
}
TreeNode *Insert(TreeNode*root,TreeNode *node)
{
    if (root == nullptr)
    {
        return node;
    }
    TreeNode *p = root;
    while (p != nullptr)
    {
        if (node->val > p->val)
        {
            if (p->left != nullptr)
            {
                p = p->left;
            }
            else
            {
                p->left = node;
            }
        }
        else
        {
            if (p->right != nullptr)
            {
                p = p->right;
            }
            else
            {
                p->right = node;
            }
        }
    }
    return root;
}
TreeNode*Delete(TreeNode*root,TreeNode*node)
{

}
 const int init[]=
    {
        1,2,3,4,5,6,7,8
    };
vector<int> _v(init,init+8);
vector<int> &v = _v;
int main(int argc,char**argv)
{

    return 0;
}
void CreateBitree(TreeNode *T)
{
    int ch;
    scanf("%c",&ch);
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        T = new TreeNode(0);
    }
    T->val = ch;
    CreateBitree(T->left);
    CreateBitree(T->right);
}