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
TreeNode * RebuildBinaryTree(int* pPreOrder, int* pInOrder, int nodeNum)
{
    if(pPreOrder == NULL || pInOrder == NULL || nodeNum <= 0)
        return NULL;
    TreeNode * pRoot = new TreeNode(0);
    // 前序遍历的第一个数据就是根节点数据
    pRoot->val = pPreOrder[0];
    pRoot->left = NULL;
    pRoot->right = NULL;
    // 查找根节点在中序遍历中的位置，中序遍历中，根节点左边为左子树，右边为右子树
    int rootPositionInOrder = -1;
    for(int i = 0; i < nodeNum; i++)
    {
        if(pInOrder[i] == pRoot->val)
        {
            rootPositionInOrder = i;
            break;
        }
    }
   
    // 重建左子树
    int nodeNumLeft = rootPositionInOrder;
    int * pPreOrderLeft = pPreOrder + 1;
    int * pInOrderLeft = pInOrder;
    pRoot->left = RebuildBinaryTree(pPreOrderLeft, pInOrderLeft, nodeNumLeft);

    // 重建右子树
    int nodeNumRight = nodeNum - nodeNumLeft - 1;
    int * pPreOrderRight = pPreOrder + 1 + nodeNumLeft;
    int * pInOrderRight = pInOrder + nodeNumLeft + 1;
    pRoot->right = RebuildBinaryTree(pPreOrderRight, pInOrderRight, nodeNumRight);

    return pRoot;
}