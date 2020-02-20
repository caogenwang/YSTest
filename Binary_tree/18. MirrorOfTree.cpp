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

TreeNode* Mirror(TreeNode*pRoot)
{
    if(pRoot == nullptr) // 返回NULL
        return nullptr;
    TreeNode * pLeft = Mirror(pRoot->left); // 求左子树镜像
    TreeNode * pRight = Mirror(pRoot->right); // 求右子树镜像
    // 交换左子树和右子树
    pRoot->left = pRight;
    pRoot->right = pLeft;
    return pRoot;
}