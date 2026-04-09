#include <iostream>
#include <queue>
using namespace std;

 //Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Solution {
public:

    //Cho một cây nhị phân, hãy tìm độ sâu tối thiểu của nó. Độ sâu tối thiểu là số nút dọc theo đường đi ngắn nhất từ nút gốc xuống nút lá gần nhất.
    //ví du:
    /*
           3
        /    \
       6       7
      /  \    /  \
     1    2   5    8
                  / \
                 1   2

    => độ sâu tối thiểu là đường đi 3 -> 6 -> 1
    */
    int minDepth(TreeNode* root)
    {
        // nếu Input: root = [] (cây rỗng) → Output: 0.
        if (!root)
        {
            return 0;//nếu cây rổng thì trả ra 0 luôn.
        }

        //nếu cây root input vào hàm là không rỗng, pass qua if (!root) thì tạo queue q .Đây là cấu trúc dữ liệu hàng đợi (FIFO – First In First Out).
        /*
        pair<TreeNode*, int>
        Mỗi phần tử trong queue không chỉ lưu node mà còn lưu thêm độ sâu của node đó.
            TreeNode* là con trỏ tới node trong cây. int là độ sâu hiện tại (ví dụ root có depth = 1, con của root depth = 2, …).
        */
        queue<pair<TreeNode*, int>> q;

        q.push({ root, 1 }); // bắt đầu từ depth = 1, bỏ root vào queue , đưa node gốc (root) của cây vào hàng đợi q. Đồng thời gắn cho nó giá trị độ sâu ban đầu là 1 (vì root nằm ở tầng đầu tiên).


        while (!q.empty()) //vòng lặp while (!q.empty()) sẽ tiếp tục chạy cho đến khi hàng đợi rỗng hoặc ta return sớm.
        {
           
            //code này  Nó giúp ta tách node thành cặp pair ra thành hai biến riêng: node và depth.node: con trỏ tới node trong cây.
            pair<TreeNode*, int> p = q.front();
            TreeNode* node = p.first;
            int depth = p.second;
            q.pop();//sau khi triết xuất được node ra khỏi queue q thì pop xóa phần tử đó trong queue .Vì queue hoạt động theo nguyên tắc FIFO (First In First Out), nên sau khi xử lý xong node đầu tiên, ta bỏ nó đi để tiếp tục với các node còn lại.

            //đem NODE đi check, nếu node đó là node LÁ!!!, không có nhánh con node->left và node->right
            // Mỗi vòng lặp lấy một node ra, kiểm tra nhánh bên trái và bên phải node đó, nếu là leaf thì trả về depth
            if (!node->left && !node->right)
            {
                return depth;//end while và trả ra kết quả độ sâu tối thiểu là của node hiện tại
            }

            //Nếu node đó, còn có giá trị trong "node->left" nghĩa là nó có nhánh con bên trái nữa
            if (node->left)
            {
                q.push({ node->left, depth + 1 });// ta push node->left đó vào queue q, và ghi độ sâu tăng lên 1 đơn vị, để while quay về chạy tiếp, xét chính node->left này.
            }

            //Nếu node đó, còn có giá trị trong "node->right" nghĩa là nó có nhánh con bên phải nữa
            if (node->right)
            {
                q.push({ node->right, depth + 1 });// ta push node->right đó vào queue q, và ghi độ sâu tăng lên 1 đơn vị, để while quay về chạy tiếp, xét chính node->right này.
            }

        }
        /*  ví dụ : root = [3,9,20,null,null,15,7]
        khởi tạo: -> q = [(3,1)]

        Vòng lặp 1: Lấy (3,1) ra khỏi queue. Node 3 không phải lá → đưa con trái và phải vào queue. -> q = [(9,2), (20,2)]
        Vòng lặp 2: Lấy (9,2) ra khỏi queue. Node 9 là lá (không có con trái/phải). Trả về depth = 2.
        */
        return 0; // không bao giờ tới đây
    }
};