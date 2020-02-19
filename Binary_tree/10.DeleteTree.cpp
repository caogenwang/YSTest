
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <map>
#include <list>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool Delete(TreeNode *p)
{
    TreeNode *q,*s;
    if (p->right == nullptr)
    {
        q = p;
        p = p->left;
        free(q);
    }
    else if (p->right == nullptr)
    {
        q = p;
        p = p->right;
        free(q);
    }
    else
    {
        q = p;
        s = p->left;
        while (s->right)
        {
            q = s;
            s = s->right;
        }
        p->val = s->val;
        if (q != p)
        {
            q->right = s->left;
        }
        else
        {
            q->left = s->left;
        }
        free(s);
    }    
}