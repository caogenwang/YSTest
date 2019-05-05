#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
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

/*****************************
3、max-points-on-a-line
一条线上最多的点
*****************************/
class Solution {
    struct Point {
        int x;
        int y;
        Point() : x(0), y(0) {}
        Point(int a, int b) : x(a), y(b) {}
 };
    
public:
    int maxPoints(vector<Point> &points) {
        size_t length = 0;
        length = points.size();
        
        if(length == 0)
            return 0;
        else if(length == 1)
            return 1;

        int ret = 0;
        for (size_t i = 0; i < length; i++)
        {
            int curmax = 1;
            map<double,int> mp;
            int vcnt = 0;
            int dup = 0;

            for (size_t j = 0; j < length; j++)
            {
                if(j != i)
                {
                    double x1 = points[i].x - points[j].x;
                    double y1 = points[i].y - points[j].y;
                    if(x1 == 0 && y1 == 0)
                    {
                        dup ++;
                    }
                    else if(x1 == 0)
                    {
                        if(vcnt == 0)
                            vcnt = 2;
                        else
                            vcnt ++;
                        curmax = max(vcnt,curmax);
                    }
                    else
                    {
                        double k = y1/x1;
                        if(mp[k] == 0)
                            mp[k] = 2;
                        else
                            mp[k]++;
                        curmax = max(mp[k],curmax);
                    } 
                }
            }
            ret = max(ret,curmax+dup);
        }
        return ret; 
    }
};