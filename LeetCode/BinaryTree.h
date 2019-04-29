#include <iostream>
#include <queue>
using namespace std;
typedef struct TreeNode_s
{
    size_t num;
    struct TreeNode_s* left;
    struct TreeNode_s* right;
}TreeNode;
class Solution {
    public:
        int run(TreeNode *root) {
            TreeNode *cur_node = nullptr;
            size_t line = 1;
            if(root == nullptr)
                return 0;
            cur_node = root;
            while(cur_node != nullptr && mQueue.size()!= 0)
            {
                mQueue.push(cur_node);
                if(cur_node->left != nullptr)
                    mQueue.push(cur_node->left);
                if(cur_node->right != nullptr)
                    mQueue.push(cur_node->right);
                cur_node = mQueue.front();
                mQueue.pop();
            }
        }
    private:
        bool is_leaf(TreeNode *node)
        {
            return (node->left == nullptr) && (node->right == nullptr);
        }
    queue<TreeNode*> mQueue;
    size_t depth;
};
/*led*/
class Solution2 {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) 
        {
            ++res;
            for (int i = q.size(); i > 0; --i) 
            {
                auto t = q.front(); 
                q.pop();
                if (!t->left && !t->right) //依次将每一行要弹出点的子节点压入队列
                    return res;
                if (t->left) 
                    q.push(t->left);
                if (t->right) 
                    q.push(t->right);
            }
        }
        return -1;
    }
};