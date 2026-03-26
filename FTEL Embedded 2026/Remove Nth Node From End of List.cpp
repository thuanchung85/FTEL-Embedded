
  
  struct ListNode {
      int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
  };
 
class Solution {
public:
    //xóa node tính từ cuối list. ví dụ cho list  head = [1,2,3,4,5], muốn xóa node vị trí n = 2 tính từ cuối list =>  head = [1,2,3,5]
    /*
    ý tưởng là:
        bước 1: Dùng two pointers (fast & slow).
        bước 2: Cho con trỏ fast chạy trước n bước. Nó sẽ nhảy tới vị trí thứ n trong link list
        bước 3: Sau đó cho cả fast và slow chạy song song đến cuối.
        Khi fast đến cuối, tự nhiên con trỏ slow sẽ đứng ngay trước node cần xóa.

Bỏ qua node đó.
    */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Tạo dummy node để xử lý trường hợp xóa node đầu, gắn next của nó là node head 
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        //Dùng two pointers (fast & slow).
        ListNode* fast = dummy;
        ListNode* slow = dummy;

        // Cho fast chạy trước n+1 bước
        //Input: [1,2,3,4,5], n=2  → fast chạy trước 3 bước, rồi cả hai chạy song song.
        //Vòng lặp for (int i = 0; i <= n; i++) fast = fast->next; chạy n+1 lần. Với n = 2, tức là chạy 3 lần.
        /*
        Bước 1: fast từ dummy → node 1.
        Bước 2: fast từ node 1 → node 2.
        Bước 3: fast từ node 2 → node 3.
        */
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // khi fast ĐANG Ở NODE 3, ta cho chạy song song 2 con trỏ fast va slow cho đến khi fast tới cuối, thì slow tự nhiên nằm ở node cần xóa.
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // thực hiện xóa node cần xóa tại con trỏ slow , bằng cách thay móc next của slow  vào slow->next->next, Bỏ qua node cần xóa
        slow->next = slow->next->next;

        return dummy->next;// sau cùng trả ra cái đầu của danh sách mới đã xóa node xong 
    }
};