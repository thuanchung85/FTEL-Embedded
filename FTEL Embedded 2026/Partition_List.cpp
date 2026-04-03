
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

class Solution {
public:
    //cho một link list  head = [1,4,3,2,5,2], sắp xếp lại link list sao cho bên trái là các số nhỏ hơn x = 3, bên phải là các số lớn hơn x = 3
    //VD: head = [1,4,3,2,5,2], x = 3  => [1,2,2,4,3,5]
    //VD: head = [2,1], x = 2 => [1,2]

    ListNode* partition(ListNode* head, int x)
    {
        // Tạo dummy nodes, beforeHead và afterHead chỉ là node giả để dễ nối.
        //nó giử vai trò là node đỉnh đầu của 2 link list sẽ tạo, dùng cho sau này ghép 2 link list thành 1 link list.
        ListNode* beforeHead = new ListNode(0);
        ListNode* afterHead = new ListNode(0);

        //before và after lần lượt trỏ đến cuối của danh sách nhỏ hơn và lớn hơn hoặc bằng x
        // tức là con trỏ before ban đầu trỏ đến chính cái dummy node beforeHead. after cũng vậy.
        /*
        thì trong bộ nhớ ta có 4 thực thể khác nhau:
        beforeHead: một node dummy (giá trị 0, next = nullptr ban đầu).
        afterHead: một node dummy khác (giá trị 0, next = nullptr ban đầu).
        before: một con trỏ, hiện tại trỏ tới cùng địa chỉ với beforeHead.
        after: một con trỏ, hiện tại trỏ tới cùng địa chỉ với afterHead.
        Như vậy đúng là có 4 biến riêng biệt, nhưng chúng tạo thành 2 cặp:
        Cặp 1: beforeHead (node) và before (con trỏ trỏ tới node đó).
        Cặp 2: afterHead (node) và after (con trỏ trỏ tới node đó).

        Điểm quan trọng:
        beforeHead và afterHead là node thật được cấp phát trên heap.
        before và after chỉ là con trỏ tham chiếu tới hai node dummy đó.
        */
        ListNode* before = beforeHead;
        ListNode* after = afterHead;

        //chạy while khi con trỏ head vẫn còn có giá trị khác null
        //Duyệt qua toàn bộ linked list:
        //Nếu node->val < x thì nối node đó vào danh sách before.
        //Nếu node->val > x thì nối vào danh sách after.
        while (head != nullptr)
        {
            //nếu giá trị value của con trỏ head lúc này nhỏ hơn x,  nối node đó vào danh sách before.
            if (head->val < x)
            {
                before->next = head;//beforeHead->next bị thay đổi ngay lần đầu tiên khi ta gặp một node < x và thực hiện before->next = head;.
                before = before->next;
            }
            //nếu giá trị value của con trỏ head lúc này lớn hơn x,  nối node vào danh sách after.
            else
            {
                after->next = head;//afterHead->next bị thay đổi ngay lần đầu tiên khi ta gặp một node > x và thực hiện after->next = head;.
                after = after->next;
            }

            //di chuyển con trỏ head tới 1 bậc tiếp theo, next. nếu nó là null thì sẽ kết thúc while
            head = head->next;
        }

        //Sau khi duyệt xong, nối đuôi của danh sách before với đầu của danh sách after.
        // Kết thúc danh sách after
        after->next = nullptr;
        // Nối before với after
        before->next = afterHead->next;//  before->next nối vào afterHead->next, chứ không nối vào afterHead, vì afterHead là con số 0.

        return beforeHead->next; // trả về beforeHead->next chinh là 1, chứ không trả về beforeHead, vì beforeHead là 0.
    }
};