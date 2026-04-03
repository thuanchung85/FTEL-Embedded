#include <iostream>
using namespace std;
//Một cây nhị phân cân bằng chiều cao (height-balanced binary tree) là cây mà ở bất kỳ node nào, chiều cao của cây con bên trái và cây con bên phải không chênh lệch quá 1. Điều này giúp cây không bị lệch hẳn về một phía, đảm bảo việc tìm kiếm, chèn, xóa đều hiệu quả.
/* chuyển head = [-10,-3,0,5,9] thành cây nhị phân cân bằng chiều cao như sau:
             0
          /    \
      - 3        9
      /  \      /  \
    -10  null   5   null

*/


// Định nghĩa ListNode, định nghĩa một kiểu dữ liệu mới tên là ListNode. Mỗi phần tử trong danh sách liên kết đơn sẽ là một ListNode.

struct ListNode {
    int val; // giá trị của node (ví dụ -10, -3, 0, ...)
    ListNode* next;  // con trỏ trỏ tới node kế tiếp trong danh sách

    //đây là constructor (hàm khởi tạo). Khi bạn tạo một node mới bằng new ListNode(5), thì: val sẽ được gán bằng 5. next sẽ được gán bằng nullptr (tức là chưa nối với node nào khác).
    ListNode(int x) : val(x), next(nullptr) {}
};

// Định nghĩa TreeNode,TreeNode cũng giống như ListNode, nhưng thay vì chỉ có một con trỏ next (trỏ sang node kế tiếp trong danh sách), thì nó có hai con trỏ:
struct TreeNode {
    int val; // giá trị của node (ví dụ 0, -3, 9, ...)
    TreeNode* left;  // trỏ sang node con bên trái
    TreeNode* right; // trỏ sang node con bên phải

    //constructor  Khi bạn tạo một node bằng new TreeNode(5) thì: val = 5 left = nullptr (chưa có cây con trái) right = nullptr (chưa có cây con phải)
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
private:
    //Khi ta muốn tạo cây nhị phân cân bằng chiều cao từ danh sách liên kết đã sắp xếp, ta cần chọn node giữa làm gốc (root) của cây. ví dụ head = [-10,-3,0,5,9] => node giữa là 0
    //Vì danh sách liên kết không cho phép truy cập trực tiếp bằng chỉ số (như mảng), ta phải dùng kỹ thuật slow/fast pointer để tìm node giữa.
    ListNode* findMiddle(ListNode* head) {
        ListNode* prev = nullptr; // lưu node trước "slow"
        ListNode* slow = head;// đi từng bước, di chuyển 1 bước mỗi lần.
        ListNode* fast = head; // đi hai bước, di chuyển 2 bước mỗi lần.
        /*ví dụ : head = [-10,-3,0,5,9]
        thì ta có :
        prev = nullptr
        slow = head (trỏ vào -10)
        fast = head (trỏ vào -10)*/

        //chạy vòng lặp while khi con trỏ fast có giá trị và còn có thể next được 
        while (fast && fast->next) {
            prev = slow; // ghi nhớ node trước slow
            slow = slow->next; // slow đi 1 bước
            fast = fast->next->next; // fast đi 2 bước
        }
        /*
        Vòng lặp 1:
        prev = slow → prev trỏ vào -10
        slow = slow->next → slow trỏ vào -3
        fast = fast->next->next → fast trỏ vào 0

        Vòng lặp 2:
        prev = slow → prev trỏ vào -3
        slow = slow->next → slow trỏ vào 0
        fast = fast->next->next → fast trỏ vào 9

        Vòng lặp 3:
        fast->next = nullptr → dừng vòng lặp.

        Lúc này:
        slow đang trỏ vào 0 (node giữa). prev trỏ vào -3.
        */

        // Khi vòng lặp kết thúc, nếu con trỏ prev khác null , lúc này prev đang trỏ là -3
        if (prev)
            prev->next = nullptr;// cắt danh sách thành hai nửa (trái và phải), để ta có thể đệ quy xây dựng cây.  cắt liên kết giữa -3 và 0.
        //Nó cắt liên kết giữa phần bên trái và phần giữa, để chia danh sách thành hai nửa. Vì vậy sau khi gọi findMiddle, danh sách ban đầu không còn nguyên vẹn nữa, mà bị tách ra.

        return slow;
        /*
        Kết quả:
        Danh sách trái: head [-10] -> [-3] -> nullptr
        Node giữa: mid [0]
        Danh sách phải: mid->next [5] -> [9] -> nullptr
        */
    }


    //Hàm bắt đầu chuyển list thành tree
public:
    //truyền head = [-10,-3,0,5,9] vào hàm
    /*
     // Tạo danh sách head [-10, -3, 0, 5, 9]
    ListNode* head = new ListNode(-10);
    head->next = new ListNode(-3);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(9);
    */
    TreeNode* sortedListToBST(ListNode* head)// hàm nhận vào là 1 con trỏ
    {
        if (!head) return nullptr;// nếu head rổng thì return null luôn 

        // Tìm node giữa bằng slow/fast pointer, lưu ý hàm findMiddle chạy xong thì list head sẽ bị thay đổi các con trỏ bên trong, cụ thể là tách làm hai.
        ListNode* mid = findMiddle(head);


        /*
        head = -10
        Gọi findMiddle(head) → trả về node 0
        Tạo root = new TreeNode(0). Lúc này root có giá trị 0.

        Kết quả:
        Danh sách trái: head [-10] -> [-3] -> nullptr
        Node giữa: mid [0]
        Danh sách phải: mid->next [5] -> [9] -> nullptr

        */
        TreeNode* root = new TreeNode(mid->val);// khởi tạo root node của tree , truyền vào giá trị của mid và nó sẽ đang bị null 2 pointer trái và phải.

        // Nếu head trùng với mid, thì return luôn root 
        if (head == mid)//Điều kiện if (head == mid) đảm bảo khi danh sách chỉ còn 1 phần tử thì dừng, tránh vòng lặp vô hạn.
            return root;

        //đệ quy, dùng lại chính hàm sortedListToBST để tìm ra tree node tiếp theo 
        root->left = sortedListToBST(head);// con trỏ bên trái của root chính là con trỏ list head  [-10] -> [-3] đem ra làm tiếp đệ quy
        /*
        Gọi sortedListToBST(head) với danh sách [-10] -> [-3]
        findMiddle → trả về node -3
        Tạo root = new TreeNode(-3)
        Gọi tiếp sortedListToBST([-10]) → trả về node -10
        Gọi sortedListToBST(nullptr) → trả về nullptr
        */
        root->right = sortedListToBST(mid->next);// con trỏ bên phải của root chính là con trỏ mid -> next là list [5] -> [9] đem ra làm tiếp đệ quy
        /*
        Nhánh phải ([5, 9]):
        findMiddle([5, 9]) → trả về 9
        Tạo TreeNode(9)
        Gọi tiếp cho trái ([5]) → tạo TreeNode(5)
        Gọi cho phải (nullptr) → trả về nullptr
        */

        return root;
    }


};