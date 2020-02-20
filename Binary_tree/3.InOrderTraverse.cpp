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
void inOrderTraverse(TreeNode* root)
{
    if( root )
    {
        inOrderTraverse(root->left);
        cout<<root->val<<' ';
        inOrderTraverse(root->right);
    }

}
/*非递归*/
void inOrderTraverse(TreeNode* root)
{
    if (!root)
        return;
    stack<TreeNode*> s_nodes;
    TreeNode *p = root;
    while (p || !s_nodes.empty())
    {
        while (p)
        {
            s_nodes.push(p);
            p = p->left;///中序现将结点进栈保存
        }///遍历到左下角尽头再出栈访问

        if (!s_nodes.empty())
        {
            p = s_nodes.top();
            s_nodes.pop();
            printf(" %c ",p->val);
            p=p->right;///遍历右孩子
        }
    }   
}
int main()
{
    return 0;
}