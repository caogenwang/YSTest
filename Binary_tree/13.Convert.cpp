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
//将二叉查找树变为有序的双向链表
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
       if (!pRootOfTree)
            return pRootOfTree;
        inOrderTraverse(pRootOfTree);

        TreeNode*p = s_nodes.top();
        TreeNode*q;
        while (p || !s_nodes.empty())
        {
            q=s_nodes.top();
            if (q)
            {
                p->left = q;
                q->right = p;
                p = q;
            }
            else
            {
                return p;
            }
            s_nodes.pop();
        }
    }
    void inOrderTraverse(TreeNode*root)
    {
        if (!root)
            return;
        inOrderTraverse(root->left);
        s_nodes.push(root);
        inOrderTraverse(root->right);
    }
private:
    stack<TreeNode*> s_nodes;
};
int main(int argc,char **argv)
{
    return 0;
}
/******************************************************************************
参数：
pRoot: 二叉查找树根节点指针
pFirstNode: 转换后双向有序链表的第一个节点指针
pLastNode: 转换后双向有序链表的最后一个节点指针
******************************************************************************/
void Convert(TreeNode * pRoot, 
             TreeNode * & pFirstNode, TreeNode * & pLastNode)
{
    TreeNode *pFirstLeft, *pLastLeft, * pFirstRight, *pLastRight;
    if(pRoot == NULL) 
    {
        pFirstNode = NULL;
        pLastNode = NULL;
        return;
    }
 
    if(pRoot->left == NULL)
    {
        // 如果左子树为空，对应双向有序链表的第一个节点是根节点
        pFirstNode = pRoot;
    }
   else
    {
        Convert(pRoot->left, pFirstLeft, pLastLeft);
        // 二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点
        pFirstNode = pFirstLeft;
        // 将根节点和左子树转换后的双向有序链表的最后一个节点连接
        pRoot->left = pLastLeft;
        pLastLeft->right = pRoot;
    }
 
    if(pRoot->right == NULL)
    {
        // 对应双向有序链表的最后一个节点是根节点
        pLastNode = pRoot;
    }
    else
    {
        Convert(pRoot->right, pFirstRight, pLastRight);
        // 对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点
        pLastNode = pLastRight;
        // 将根节点和右子树转换后的双向有序链表的第一个节点连接
        pRoot->right = pFirstRight;
        pFirstRight->left = pRoot;
    }
    return;
}