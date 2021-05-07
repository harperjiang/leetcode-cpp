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
            if (root == nullptr) {
                return 0;
            }
            int left_size = serialize_withsize(buffer, root->left);
            int right_size = serialize_withsize(buffer, root->right);

            return left_size + right_size +
                   write_int(buffer, left_size) +
                   write_int(buffer, right_size) +
                   write_int(buffer, root->val);
        }

        TreeNode *deserialize_withsize(string &buffer, int position) {
            if(position<=0) {
                return nullptr;
            }
            // read sizes
            int val = read_int(buffer, position - 4);
            int left_size = read_int(buffer, position - 12);
            int right_size = read_int(buffer, position - 8);

            TreeNode *node = new TreeNode(val);
            if (left_size != 0) {
                node->left = deserialize_withsize(buffer, position - 12 - right_size );
            }
            if (right_size != 0) {
                node->right = deserialize_withsize(buffer, position - 12 );
            }
            return node;
        }

        int write_int(string &buffer, int val) {
            buffer.append((const char *) &val, 4);
            return 4;
        }

        int read_int(string &buffer, int pos) {
            return *(int *) (buffer.data() + pos);
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
            return deserialize_withsize(data, data.size());
        }
    };

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

    void run() {
        Codec ser, deser;

        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->left = new TreeNode(4);
        root->right->right= new TreeNode(5);
        TreeNode *ans = deser.deserialize(ser.serialize(root));

        delete root->right->left;
        delete root->right->right;
        delete root->left;
        delete root->right;
        delete root;

        delete ans->right->left;
        delete ans->right->right;
        delete ans->left;
        delete ans->right;
        delete ans;

        return;
    }

}
#endif //LEETCODE_LC297_H
