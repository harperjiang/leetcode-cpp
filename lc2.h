
namespace lc2 {
    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}

        ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    class Solution {
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
            ListNode *l1p = l1;
            ListNode *l2p = l2;
            ListNode *result_header = new ListNode();
            ListNode *result_pointer = result_header;
            ListNode *prev_digit = nullptr;

            do {
                int sum = (l1p ? l1p->val : 0) + (l2p ? l2p->val : 0) + result_pointer->val;
                int carry = sum / 10;
                sum %= 10;

                result_pointer->val = sum;

                prev_digit = result_pointer;

                auto next = new ListNode(carry);
                result_pointer->next = next;
                result_pointer = next;

                l1p = l1p ? l1p->next : nullptr;
                l2p = l2p ? l2p->next : nullptr;

            } while (l1p || l2p);

            // Delete leading zero
            if (result_pointer->val == 0) {
                delete result_pointer;
                prev_digit->next = nullptr;
            }

            return result_header;

        }
    };

    int run() {
        auto a1 = new ListNode(9);
        auto a2 = new ListNode(9,a1);
        auto a3 = new ListNode(9, a2);
        auto a4 = new ListNode(9, a3);
        auto a5 = new ListNode(9, a4);
        auto a6 = new ListNode(9, a5);
        auto a7 = new ListNode(9, a6);

        auto b1 = new ListNode(9);
        auto b2 = new ListNode(9,b1);
        auto b3 = new ListNode(9, b2);
        auto b4 = new ListNode(9, b3);

        Solution solution;

        auto result = solution.addTwoNumbers(a7, b4);

        while(result!= nullptr) {
            std::cout << result->val;
            result = result->next;
        }
        std::cout << '\n';
        return 0;
    }


}