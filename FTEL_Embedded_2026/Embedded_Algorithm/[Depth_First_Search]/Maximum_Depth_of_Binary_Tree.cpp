#include <cstddef>
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
    //Cho 1 cây root = [3,9,20,null,null,15,7], tìm ra độ sâu max của nó.
    int maxDepth(TreeNode* root)
    {
        if (root == NULL) return 0; // cây rỗng, chốt chặn tại node lá để stop đệ quy khi chạy tới node lá 

        //Mỗi lần hàm maxDepth chạy thành công trên một node thì nó sẽ +1 để tính thêm độ sâu của chính node đó.
        //Cách chạy đệ quy trong hàm maxDepth chính là đi xuống một mạch đến tận node lá sâu nhất (theo kiểu DFS – Depth First Search). 
        //Khi gặp node lá (không có con trái, con phải), hàm trả về 1. Sau đó, khi quay ngược lên, mỗi tầng sẽ cộng thêm 1 để tính độ sâu của chính node đó.
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);


        //check max 2 phần tử node 2 bên, lấy ra giá trị cao nhất.
        return 1 + max(leftDepth, rightDepth);
    }
};