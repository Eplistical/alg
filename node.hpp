#ifndef _NODE_HPP
#define _NODE_HPP

#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <queue>

namespace {

    // singly-linked list node
    struct ListNode {
        public:
            int val;
            ListNode *next;
            ListNode(int x) : val(x), next(NULL) {}

        public:
            std::string to_str() {
                // convert to string for output
                ListNode* p = this;
                std::string rst = "[";
                while (p) {
                    rst += std::to_string(p->val) + ",";
                    p = p->next;
                }
                rst[rst.size() - 1] = ']';
                return rst;
            } 
    };

    // binary tree node
    struct TreeNode {
        public:
            int val;
            TreeNode *left;
            TreeNode *right;
            TreeNode(int x) : val(x), left(NULL), right(NULL) {}

        public:
            std::string to_str() {
                // convert to string output
                // BFS
                std::string rst = "[";
                std::queue<std::pair<TreeNode*, int>> q, qnext;

                TreeNode* cur;
                int idx;
                int curidx = 0;
                q.push(std::make_pair(this, 0));
                while (not q.empty()) {
                    // get first 
                    cur = q.front().first;
                    idx = q.front().second;
                    q.pop();
                    // append nodes 
                    while (curidx < idx) {
                        rst += "null,";
                        curidx += 1;
                    }
                    rst += std::to_string(cur->val) + ",";
                    curidx += 1;
                    // construct qnext
                    if (cur->left) {
                        qnext.push(std::make_pair(cur->left, idx*2));
                    }
                    if (cur->right) {
                        qnext.push(std::make_pair(cur->right, idx*2+1));
                    }
                    // end of q
                    if (q.empty()) {
                        q.swap(qnext);
                        curidx = 0;
                    }
                }
                rst[rst.size() - 1] = ']';
                return rst;
            } 
    };

};

#endif 
