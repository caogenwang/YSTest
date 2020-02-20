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

//叶子节点的个数
int GetLeafNodeNum(TreeNode * pRoot)
{
    if (!pRoot)
        return 0;

    if (pRoot->left == nullptr && pRoot->right == nullptr)
        return 1;

    if (pRoot->left == nullptr && pRoot->right != nullptr)
        return GetLeafNodeNum(pRoot->right);

    if (pRoot->left != nullptr && pRoot->right == nullptr)
        return GetLeafNodeNum(pRoot->left);
    
    if (pRoot->left != nullptr && pRoot->right != nullptr)
        return GetLeafNodeNum(pRoot->left) + GetLeafNodeNum(pRoot->right);

}

int GetLeafNodeNum1(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return 0;
    if(pRoot->left == NULL && pRoot->right == NULL)
        return 1;
    int numLeft = GetLeafNodeNum(pRoot->left); // 左子树中叶节点的个数
    int numRight = GetLeafNodeNum(pRoot->right); // 右子树中叶节点的个数
    return (numLeft + numRight);
}
