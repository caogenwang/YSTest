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

bool isAvlTree(TreeNode*pRoot)
{
    if (!pRoot)
        return true;
    int left_depth = DepthOfAvlTree(pRoot->left);
    int right_depth = DepthOfAvlTree(pRoot->right);

    if ((left_depth - right_depth) >= 2 || (left_depth - right_depth) <= -2)
        return false;
    else
        return isAvlTree(pRoot->left) && isAvlTree(pRoot->right);;
}
int DepthOfAvlTree(TreeNode*pRoot)
{
    if (!pRoot)
        return 0;
    int nleft = DepthOfAvlTree(pRoot->left);
    int nright = DepthOfAvlTree(pRoot->right);

    return (nleft>nright)?(nleft+1):(nright+1);
}

class Solution {
    int TreeDepth(TreeNode* pRoot)
    {
        if(pRoot == nullptr)
            return 0;
        int nleft = TreeDepth(pRoot->left);
        int nright = TreeDepth(pRoot->right);
 
        return (nleft>nright)?(nleft+1):(nright+1);
    }
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if(pRoot == nullptr)
            return true;
        int nleft = TreeDepth(pRoot->left);
        int nright = TreeDepth(pRoot->right);
        int diff = nleft - nright;
        if(diff > 1 || diff < -1)
            return false;
        return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
    }
};