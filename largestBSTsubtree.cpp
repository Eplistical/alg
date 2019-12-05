#include <iostream>
#include <vector>
#include <algorithm>
#include "node.hpp"

using namespace std;

TreeNode* largestBSTsubtree_helper(TreeNode* root, int& N, int& minv, int& maxv) {
    if (!root) {
        // trival case
        N = 0;
        return NULL;
    }
    else {
        int Nl, Nr, minvl, minvr, maxvl, maxvr;
        TreeNode* bstl = largestBSTsubtree_helper(root->left, Nl, minvl, maxvl);
        TreeNode* bstr = largestBSTsubtree_helper(root->right, Nr, minvr, maxvr);

        if (bstl == root->left and bstr == root->right and (Nl == 0 or root->val > maxvl) and (Nr == 0 or root->val < minvr)) {
            // root as max subtree
            N = Nl + Nr + 1;
            minv = (Nl > 0 ? minvl : root->val);
            maxv = (Nr > 0 ? maxvr : root->val);
            return root;
        }
        else if (Nl >= Nr) {
            // bstl as max subtree
            N = Nl;
            minv = minvl;
            maxv = maxvl;
            return bstl;
        }
        else {
            // bstr as max subtree
            N = Nr;
            minv = minvr;
            maxv = maxvr;
            return bstr;
        }

    }
}

TreeNode* largestBSTsubtree(TreeNode* root) {
    int N, minv, maxv;
    return largestBSTsubtree_helper(root, N, minv, maxv);
}

int main(int argc, char** argv) {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right= new TreeNode(8);
    //root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(7);

    cout << root->to_str() << endl;

    TreeNode* bst = largestBSTsubtree(root);
    cout << bst->to_str() << endl;
    return 0;
}
