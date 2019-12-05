#include <iostream>
#include "node.hpp"


using namespace std;

int main(int argc, char** argv) {

    ListNode* head = new ListNode(0);
    ListNode* p = head;

    p->next = new ListNode(4);
    p = p->next;
    p->next = new ListNode(6);
    p = p->next;
    p->next = new ListNode(7);
    p = p->next;
    p->next = new ListNode(9);
    p = p->next;
    p->next = new ListNode(10);
    p = p->next;

    cout << head->to_str() << endl;


    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    //root->left->right = new TreeNode(5);
    //root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->right->right = new TreeNode(9);
    cout << root->to_str() << endl;

   
    return 0;
}
