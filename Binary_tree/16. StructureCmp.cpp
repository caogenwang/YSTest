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

bool StructureCmp(TreeNode * pRoot1, TreeNode * pRoot2)
{
    if (pRoot1 == nullptr && pRoot2 == nullptr)
        return true;
    if ((pRoot1 == nullptr && pRoot2 != nullptr)
    || (pRoot1 != nullptr && pRoot2 == nullptr))
        return false;
    
    return StructureCmp(pRoot1->left,pRoot2->left) && StructureCmp(pRoot1->right,pRoot2->right);
}