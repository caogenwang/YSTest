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

int GetMaxDistance(TreeNode * pRoot, int & maxLeft, int & maxRight)
{
    // maxLeft, 左子树中的节点距离根节点的最远距离
    // maxRight, 右子树中的节点距离根节点的最远距离
    if(pRoot == NULL)
    {
        maxLeft = 0;
        maxRight = 0;
        return 0;
    }
    int maxLL, maxLR, maxRL, maxRR;
    int maxDistLeft, maxDistRight;
    if(pRoot->left != NULL)
    {
        maxDistLeft = GetMaxDistance(pRoot->left, maxLL, maxLR);
        maxLeft = max(maxLL, maxLR) + 1;
    }
    else
    {
        maxDistLeft = 0;
        maxLeft = 0;
    }
    if(pRoot->right != NULL)
    {
        maxDistRight = GetMaxDistance(pRoot->right, maxRL, maxRR);
        maxRight = max(maxRL, maxRR) + 1;
    }
    else
    {
        maxDistRight = 0;
        maxRight = 0;
    }
    return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}