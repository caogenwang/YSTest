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
void LevelTraverse(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    queue<TreeNode *> q;
    q.push(pRoot);
    while(!q.empty())
    {
        TreeNode * pNode = q.front();
        q.pop();
        cout<<pNode->val<<" "<<endl;
        if(pNode->left != NULL)
            q.push(pNode->left);
        if(pNode->right != NULL)
            q.push(pNode->right);
    }
    return;
}

int main(int argc,char **argv)
{
    return 0;
}
void LevelTraverse(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    queue<TreeNode*> q_nodes;
    q_nodes.push(pRoot);
    while (!q_nodes.empty())
    {
        TreeNode *temp = q_nodes.front();
        q_nodes.pop();
        cout<<temp->val<<" "<<endl;
        if (!temp->left)
        {
            q_nodes.push(temp->left);
        }
        if (!temp->right)
        {
            q_nodes.push(temp->right);
        }
    }   
}