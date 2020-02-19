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


void inOrderTraverse(TreeNode* root)
{
    if( root )
    {
        inOrderTraverse(root->left);
        cout<<root->val<<' ';
        inOrderTraverse(root->right);
    }

}
int main()
{
    return 0;
}