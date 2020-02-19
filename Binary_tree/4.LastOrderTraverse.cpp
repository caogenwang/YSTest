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


void lastOrderTraverse(TreeNode* root)
{
    if( root )
    {
        lastOrderTraverse(root->left);
        lastOrderTraverse(root->right);
        cout<<root->val<<' ';
    }

}
int main()
{
    return 0;
}