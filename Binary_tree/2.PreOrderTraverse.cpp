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
void preOrderTraverse(TreeNode* root)
{
    if( root )
    {
        cout<<root->val<<' ';
        preOrderTraverse(root->left);
        preOrderTraverse(root->right);
    }

}
int main()
{
    return 0;
}
/*非递归*/
void preOrderTraverse(TreeNode* root)
{
    if (!root)
        return;
    stack<TreeNode*> s_nodes;
    TreeNode *p = root;
    s_nodes.push(root);
    while (p || s_nodes.empty())
    {
        while (p)///到最左下的孩子
        {
            cout<<p->val<<" "<<endl;///先序先遍历结点
            s_nodes.push(p);
            p = p->left;
        }
        if (!s_nodes.empty())///在栈不为空的情况下，左孩子为空，弹出该结点，遍历右孩子
        {
            p = s_nodes.top();
            s_nodes.pop();
            p = p->right;
        }
    }
}