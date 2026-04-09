#include <iostream>
#include <queue>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};


class Solution {
public:
    int maxDepth(Node* root)
    {
        if (root == nullptr)//Nếu cây rỗng → độ sâu = 0.
            return 0;

        int depth = 0;

        //Với mỗi node, ta tính độ sâu lớn nhất của các node con rồi cộng thêm 1.
        //root->children là một vector<Node>*, tức là danh sách các con của node hiện tại.
        //mỗi child là một dạng Node*
        for (auto child : root->children) // câu lệnh này giúp ta duyệt qua tất cả các node con của một node mà không cần viết vòng lặp chỉ số for (int i = 0; i < ...; i++).
        {
            depth = max(depth, maxDepth(child));//Ta gọi đệ quy maxDepth(child) để tính độ sâu của cây con đó. Sau đó lấy giá trị lớn nhất trong tất cả các cây con.
        }

        return depth + 1;// chạy qua hết for thì tăng depth lên 1 .

        /*
        ví dụ : Chuỗi [1,null,3,2,4,null,5,6]. 1 là root. Sau null là nhóm con của 1: gồm 3, 2, 4. Sau null tiếp theo là nhóm con của 3: gồm 5, 6.
                 1
             /   |   \
            3    2    4
           / \
          5   6

         for lần đầu chạy check node root = 1 -> Gọi đệ  quy truyền root node = 1 vào chính hàm maxDepth(1), lúc này biến còn depth = 0 .
         trong lần đệ quy maxDepth(1) vòng for trong đó sẽ Duyệt các con: 3, 2, 4. khi check node = 3.
                -> đệ quy Với child = 3 gọi hàm maxDepth(3):
                            -> đệ quy Gọi maxDepth(3) Duyệt con của 3 là : 5, 6 . -> đệ quy tiếp maxDepth(5) → không có con → trả về 1 .
                                for tiếp -> đệ quy maxDepth(6) → không có con → trả về 1 .

                                Trong vòng for, biến depth được cập nhật thành max(0,1) rồi max(1,1) → cuối cùng depth = 1. Sau đó return depth + 1 => 1 + 1 = 2. Nghĩa là node 3 có độ sâu là 2 (tính cả chính nó).

        for chạy Với child = 2: maxDepth(2) → không có con → trả về 1
        for chạy Với child = 4: maxDepth(4) → không có con → trả về 1
        Quay lại maxDepth(1): depth = max(0,2,1,1) = 2 => Trả về 2 + 1 (vì có root node) = 3
        */
    }
};