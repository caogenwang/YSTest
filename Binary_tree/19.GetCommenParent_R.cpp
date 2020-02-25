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

//求两个节点的最低公共祖先(递归解法)
TreeNode* GetCommenParent_R(TreeNode* root, TreeNode* bstn1, TreeNode* bstn2)
{
    if (root==nullptr || bstn1==nullptr || bstn2==nullptr)
        return root;
    if (bstn1->val < root->val && bstn2->val < root->val)
        return GetCommenParent_R(root->left,bstn1,bstn2);
    else if (bstn1->val > root->val && bstn2->val > root->val)
        return GetCommenParent_R(root->right,bstn1,bstn2);
    else
        return root;
}

bool GetNodePath(TreeNode * pRoot, TreeNode * pNode, 
                 list<TreeNode *> & path)
{
    if(pRoot == pNode)
    {   
        path.push_back(pRoot);
        return true;
    }
    if(pRoot == NULL)
       return false;
    path.push_back(pRoot);
    bool found = false;
    found = GetNodePath(pRoot->left, pNode, path);
    if(!found)
        found = GetNodePath(pRoot->right, pNode, path);
    if(!found)
        path.pop_back();
    return found;
}
TreeNode * GetLastCommonParent(TreeNode * pRoot, TreeNode * pNode1, TreeNode * pNode2)
{
    if(pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
        return NULL;
    list<TreeNode*> path1;
    bool bResult1 = GetNodePath(pRoot, pNode1, path1);
    list<TreeNode*> path2;
    bool bResult2 = GetNodePath(pRoot, pNode2, path2);
    if(!bResult1 || !bResult2) 
        return NULL;
    TreeNode * pLast = NULL;
    list<TreeNode*>::const_iterator iter1 = path1.begin();
    list<TreeNode*>::const_iterator iter2 = path2.begin();
    while(iter1 != path1.end() && iter2 != path2.end())
    {
        if(*iter1 == *iter2)
            pLast = *iter1;
        else
            break;
        iter1++;
        iter2++;
    }
    return pLast;
}