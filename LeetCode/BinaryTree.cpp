#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "BinaryTree.h"
using namespace std;
/*****************************
1、minimum-depth-of-binary-tree
*****************************/
//递归:
class Solution {
public:
    int run(TreeNode *root) {
        if(root == nullptr)
            return 0;
        if(root->left == nullptr) return 1 + run(root->right);
        if(root->right == nullptr) return 1 + run(root->left);
        return 1 + min(run(root->left), run(root->right));
    }
};
//迭代
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) {
            ++res;
            for (int i = q.size(); i > 0; --i) {//一层一层的遍历，一个for循环就是一层
                auto t = q.front(); q.pop();
                if (!t->left && !t->right) return res;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return -1;
    }
};

/*****************************
2、evaluate-reverse-polish-notation
*****************************/
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> s; 
        size_t result = 0;
        for(size_t i = 0; i < tokens.size(); i++)
        {
            if(tokens[i] == "+" || tokens[i] == "-" ||
            tokens[i] == "*" ||tokens[i] == "/" )
            {
                if(s.size() < 2) return 0;
                int a = s.top();s.pop();
                int b = s.top();s.pop();
                if (tokens[i] == "+")
                {
                    result = a + b;
                    s.push(result);
                }else if(tokens[i] == "-")
                {
                    result = a - b;
                    s.push(result);
                }
                else if(tokens[i] == "*")
                {
                    result = a * b;
                    s.push(result);
                }
                else if(tokens[i] == "/")
                {
                    result = a / b;
                    s.push(result);
                }
                
            }
            else
            {
                s.push(atoi(tokens[i].c_str()));
            }
            
        } 
    }
};