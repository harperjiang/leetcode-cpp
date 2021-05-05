//
// Created by harper on 5/5/21.
//

#ifndef LEETCODE_LC297_H
#define LEETCODE_LC297_H

#include <string>

using namespace std;

namespace lc297 {
    /**
 * Definition for a binary tree node.
     **/
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Codec {
    protected:
        int serialize_withsize(string &buffer, TreeNode *root) {
            int left_size = serialize_withsize(buffer, root->left);
            int right_size = serialize_withsize(buffer, root->right);

            write_int(buffer, left_size);
            write_int(buffer, right_size);
            write_int(buffer, root->val);
        }

        void write_int(string &buffer, int val) {

        }

    public:

        // Encodes a tree to a single string.
        string serialize(TreeNode *root) {
            string buffer;
            serialize_withsize(buffer, root);
            return buffer;
        }

        // Decodes your encoded data to tree.
        TreeNode *deserialize(string data) {

        }
    };

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

    void run() {

    }

}
#endif //LEETCODE_LC297_H
