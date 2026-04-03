
#include <iostream>
using namespace std;
//cho một link list   [1,2,6,3,4,5,6], hãy xóa phần tử có giá trị 6 =>  Output: [1,2,3,4,5]

// Định nghĩa cấu trúc ListNode

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    // Hàm hỗ trợ in danh sách
    void printList(ListNode* head) {
        while (head != nullptr) {
            cout << head->val;
            if (head->next)
                cout << " -> ";
            head = head->next;
        }
        cout << endl;
    }

public:
    //Giả sử input: head = [1,2,6,3,4,5,6], val = 6
    ListNode* removeElements(ListNode* head, int val)
    {
        // Tạo dummy node trỏ tới head, ta tạo một dummy node đứng trước head để dễ xử lý khi node đầu cũng cần xóa.
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        //dummy -> 0 -> 1 -> 2 -> 6 -> 3 -> 4 -> 5 -> 6 ,  curr = dummy

        ListNode* curr = dummy;//Dùng con trỏ curr duyệt qua danh sách, luôn kiểm tra curr->next.

        while (curr->next != nullptr)
        {
            //Nếu curr->next->val == val thì bỏ qua node đó (xóa).
            if (curr->next->val == val)
            {
                // Xóa node bằng cách bỏ qua nó
                ListNode* temp = curr->next;
                curr->next = curr->next->next;//đẩy next của con trỏ curr->next tiến tới móc vào phần tử sau nữa, điều này làm cho curr->next bị bỏ qua mất một phần tử trong link list
                delete temp; // giải phóng bộ nhớ
                /*
                curr->next chính là node cần xóa.
                Nếu viết thẳng curr->next = curr->next->next; thì sau dòng này, bạn mất đi địa chỉ của node cần xóa.
                → Không còn cách nào để gọi delete cho node đó nữa, dẫn đến rò rỉ bộ nhớ.
                */
            }
            //Nếu không thì di chuyển curr sang node tiếp theo.
            else
            {
                curr = curr->next;
            }
        }
        /* chay while
        curr = dummy, curr->next = 1 → không bằng 6 -> chạy else → curr sang node 1.
        curr = 1, curr->next = 2 → không bằng 6 -> chạy else → curr sang node 2.
        curr = 2, curr->next = 6 → bằng 6 -> chạy if → xóa node 6.
        curr->next = 3
        danh sách: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6

        curr = 2, curr->next = 3 → không bằng 6 -> chạy else → curr sang node 3.
        curr = 3, curr->next = 4 → không bằng 6 -> chạy else → curr sang node 4.
        curr = 4, curr->next = 5 → không bằng 6 -> chạy else → curr sang node 5.
        curr = 5, curr->next = 6 → bằng 6 -> chạy if → xóa node 6.

        curr->next = nullptr
        thoát while
        danh sách: 0 -> 1 -> 2 -> 3 -> 4 -> 5
        */

        ListNode* newHead = dummy->next;// trả lại new head cho con số 1

        delete dummy; // giải phóng dummy

        return newHead;
    }
};