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
    int bf;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*         
              P                       P                       L
            /   \                   /   \                   /   \
           /     \                 /     \                 /     \
          L       Pr  -------->   L      Pr  -------->    Ll      P
         /  \                    /  \                    /       /  \
        /    \                  /    \                  N       Lr   Pr
        Ll    Lr               Ll    Lr
                                |
                                N
*/

void R_Rotate(TreeNode *p)
{
    TreeNode *L;
    L = p->left;
    p->left = L->right;
    L->right = p;
    p = L;
}
/*
       P                            P                              L
    /     \                       /    \                         /   \
   Pl      L       -------->     Pl     L        -------->      P     Lr
         /   \                        /   \                   /   \     \
        Ll   Lr                     Ll     Lr                Pl    Ll    N
                                            |
                                            N   
*/
void L_rotate(TreeNode *p)
{
    TreeNode *R = p->right;
    p->right = R->left;
    R->left = p;
    p = R;
}
#define LH +1
#define EH 0
#define RH -1
void LeftBalance(TreeNode *T)
{
    TreeNode *L,*Lr;
    L = T->left;
    switch(L->bf)
    {
        case LH:
        
            break;
        
    }
}