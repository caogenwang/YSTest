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