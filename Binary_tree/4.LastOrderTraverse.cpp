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

/*递归*/
void lastOrderTraverse(TreeNode* root)
{
    if( root )
    {
        lastOrderTraverse(root->left);
        lastOrderTraverse(root->right);
        cout<<root->val<<' ';
    }

}

/*非递归*/
void lastOrderTraverse(TreeNode* root)
{
    if(!root)
        return;
    stack<TreeNode*> s_nodes;
    TreeNode*p = root;
    while (p || !s_nodes.empty())
    {
        while (p)
        {
            s_nodes.push(p);
            p = p->left;
        }
        if (!s_nodes.empty())
        {
            p = s_nodes.top();
            s_nodes.pop();
            p = p->right;
        }
        
        
    }
    
}

int main()
{
    return 0;
}