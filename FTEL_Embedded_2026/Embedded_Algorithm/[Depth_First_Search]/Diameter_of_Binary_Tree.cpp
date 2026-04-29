#include <algorithm>
using namespace std;

 // Definition for a binary tree node.
  struct TreeNode {
     int val;
      TreeNode *left;
      TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
 
class Solution {
public:
    /*
        Cho trước gốc của một cây nhị phân, trả về chiều dài của đường kính của cây. Đường kính của một cây nhị phân là chiều dài của đường đi dài nhất giữa bất kỳ hai nút nào trong cây.
        Đường đi này có thể có hoặc không đi qua gốc. Chiều dài của một đường đi giữa hai nút được biểu diễn bằng số cạnh giữa chúng.

        VÍ DỤ: root = [1,2,3,4,5]
                  1
                /  \
               2    3
             /   \
            4     5

            chiều dài có thể dài nhất llà [4,2,1,3] gồm các cạnh sau: cạnh 4_2, cạnh 2_1, cạnh 1_3 => suy ra là chiều dài của đường kính của cây là = 3


        Đường kính của cây = số cạnh dài nhất giữa hai node bất kỳ.
        Với mỗi node, ta tính:
        Chiều cao của cây con trái.
        Chiều cao của cây con phải.
        Tổng hai chiều cao này chính là độ dài đường đi qua node đó.
        Đường kính của cây = giá trị lớn nhất trong tất cả các node.
    */
    int diameter = 0;

    //hàm đệ quy
    int depth(TreeNode* root)
    {
        if (!root) return 0;//nếu cây rổng thì end hàm

        int left = depth(root->left);
        int right = depth(root->right);
        /*
        Bắt đầu tại node 1: hàm depth gọi sang cây con trái → node 2.
        Tại node 2: lại gọi tiếp xuống cây con trái → node 4.
        Tại node 4: vì không có con trái/phải, hàm trả về 0.
        Sau khi tính xong node 4, hàm quay ngược lên node 2 để tính tiếp cây con phải (node 5).
        Node 5 cũng trả về 0, rồi node 2 tính được chiều cao = max(0,0)+1 = 1.
        Cuối cùng quay ngược về node 1, lấy kết quả từ node 2 (left depth) và node 3 (right depth).
        Node 3 không có con trái → depth(root->left) = depth(NULL) = 0.
        Node 3 cũng không có con phải → depth(root->right) = depth(NULL) = 0. kết quả node 3 có chiều cao = 1,

        Node 4 và 5 cũng tương tự: không có con → left=0, right=0, chiều cao=1.
        Node 2: left=1 (từ node 4), right=1 (từ node 5) → chiều cao=2, đường kính qua node 2 = 2.
        Node 1: left=2 (từ node 2), right=1 (từ node 3) → chiều cao=3, đường kính qua node 1 = 3.

        Đó là lý do kết quả cuối cùng là 3.
        Đây chính là cơ chế đệ quy theo chiều sâu (DFS): đi xuống hết nhánh trái, tính xong, rồi quay ngược lên, sau đó đi tiếp nhánh phải.
        */


        // cập nhật đường kính, đường kính là tính cả chiều dài của nhánh trái và phải cộng lại.
        diameter = max(diameter, left + right);

        // trả về chiều cao
        /*
        Tại node 2: khi tính depth(node 2), nó lấy chiều cao từ node 4 (1) và node 5 (1), rồi cộng thêm chính node 2 → tổng chiều cao = 2.
        Lúc này node 2 trở thành “vô địch tạm thời” vì nhánh của nó dài nhất (cao hơn node 3).

        Nhưng khi quay về node 1, nó kết hợp chiều cao của node 2 (2) với chiều cao của node 3 (1). Tổng = 3, và đó mới là đường kính cuối cùng.
        Nói cách khác: node 2 đúng là “vô địch” cho tới khi node 1 kết hợp thêm node 3, tạo ra đường đi dài hơn.

        Nếu vẽ sơ đồ thì sẽ thấy rõ:
        Node 4 và 5: height = 1
        Node 2: height = 2 (vô địch tạm thời)
        Node 3: height = 1
        Node 1: height = 3 (vô địch cuối cùng, vì kết hợp cả nhánh trái và phải).
        */
        return max(left, right) + 1;

        /* ví dụ nếu ta nối 1 cây thế này, thêm node 6 dưới chân node 5
                    1
                   / \
                  2   3
                 / \
                4   5
                     \
                      6

            Tính toán từng node
                Node 6: không có con → height = 1.
                Node 5: left = 0, right = 1 (từ node 6) → height = max(0,1)+1 = 2.
                Node 4: height = 1.
                Node 2: left = 1 (node 4), right = 2 (node 5) → height = max(1,2)+1 = 3.
                Node 3: height = 1.
                Node 1: left = 3 (node 2), right = 1 (node 3) → height = max(3,1)+1 = 4.

            Đường kính
                Qua node 2: left+right = 1+2 = 3.
                Qua node 1: left+right = 3+1 = 4.
                Vậy đường kính mới = 4, chính là đường đi [4 → 2 → 5 → 6] hoặc [6 → 5 → 2 → 1 → 3].
        */
    }

    //hàm chính
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return diameter;
    }
};