#include <cstddef>


  struct ListNode {
      int val;
      ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    /*
     Ta cần xóa một node trong link list. Nhưng Ta không có quyền truy cập vào head, mà chỉ được đưa cho chính cái node cần xóa.
      Vì node đó không phải node cuối, ta có thể giải quyết bằng cách chép dữ liệu từ node kế tiếp vào node hiện tại, rồi bỏ qua node kế tiếp.
    */
    void deleteNode(ListNode* node) {
        // Sao chép giá trị từ node kế tiếp , chép đè lên node này
        node->val = node->next->val;

        // Bỏ qua node kế tiếp, móc con trỏ next của nó vào node->next
        node->next = node->next->next;
    }
};