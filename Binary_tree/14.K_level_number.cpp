#include <string>
#include <iostream>
#include <stack>
#include <map>
#include <list>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//二叉树第k层的节点个数
int GetNodeNumKthLevel(TreeNode * pRoot, int k)
{
    if (!pRoot || k<0)
        return 0;
    if (k == 1)
        return 1;
    return GetNodeNumKthLevel(pRoot->left, k-1) + GetNodeNumKthLevel(pRoot->right, k-1);
    
    
}
int main(int argc,char **argv)
{
    return 0;
}