#include <iostream>
#include <queue>
using namespace std;

class Solution {

    /*
        Trong C++ thì graph (đồ thị) không phải là một kiểu dữ liệu có sẵn, mà
       ta thường biểu diễn nó bằng các cấu trúc dữ liệu như: vector<vector<int>>
      ví du: graph = [
                        [1,2,3],
                        [0,2],
                        [0,1,3],
                        [0,2]
                        ]
                         Mỗi phần tử con (một vector) biểu diễn 1 node cụ thể:

            graph[0] = [1,2,3] → nghĩa là node 0 có cạnh nối với các node 1, 2, 3.

            graph[1] = [0,2] → nghĩa là node 1 có cạnh nối với node 0 và 2.

            graph[2] = [0,1,3] → nghĩa là node 2 có cạnh nối với node 0, 1, 3.

            graph[3] = [0,2] → nghĩa là node 3 có cạnh nối với node 0 và 2.


        ==> Đồ thị lưỡng phân là một loại đồ thị mà các node có thể được nhóm thành các nhóm:
            - trong 1 nhóm bất kỳ sẽ không có kết nối nào giữa 2 node bất kỳ, nghĩa là trong cùng một nhóm: không có cạnh nào nối hai node với nhau.
            - 1 node bất kỳ trong nhóm A sẽ ít nhất một kết nối tới node của nhóm B, nghĩa là giữa hai nhóm: mọi cạnh đều nối từ một node của nhóm A sang một node của nhóm B.

            Giả sử ta có đồ thị graph = [[1,3],[0,2],[1,3],[0,2]] với các cạnh: (0–1), (0–3), (2–1), (2–3).

            0---1
            |   |
            3---2

            Ta chia thành:

            Nhóm A = {0, 2}

            Nhóm B = {1, 3}

            Rõ ràng: không có cạnh nào nối giữa hai đỉnh trong cùng nhóm {0, 2} không có 0 nối với 2 ,và {1, 3} 1 không nối với 3. Tất cả cạnh đều nối từ A sang B → đây là đồ thị lưỡng phân.
    */

public:
    bool isBipartite(vector<vector<int>>& graph)
    {
        //ví du graph = [[1,3],[0,2],[1,3],[0,2]]
        int n = graph.size(); // biến ghi lại số hàng của graph 4
        vector<int> array_check_node_color(n, -1); // một array độ dài bằng n tất cả -1 array_check_node = [-1,-1,-1,-1]

        //duyệt hết các node trong graph, Đồng thời check so kè với array_check_node
        for (int i = 0; i < n; ++i)
        {
            if (array_check_node_color[i] == -1) //nếu tại index node đó mà array_check_node có giá trị = -1, thì ta save giá trị index vào queueNode_index
            {
                queue<int> queueNode_index;
                queueNode_index.push(i);//save index của node vào queueNode_index

                array_check_node_color[i] = 0; // gắn giá trị -1 về 0 để loại bỏ phần tử, không đem nó chạy code nữa => array_check_node = [0,-1,-1,-1]

                //chạy while check từng phần tử của queueNode_index ví dụ queueNode_index = [0...1...3]. giải thuật này làm việc check các node TRONG cùng NHÓM
                while (!queueNode_index.empty())
                {
                    int nodeIndex = queueNode_index.front();// đem giá trị của phần tử đầu tiên trong queueNode_index ra xữ lý , ví dụ lúc này (nodeIndex = 0)
                    queueNode_index.pop();// remove nó khỏi queueNode_index, để khỏi chạy lại xử lý nó


                    for (int v : graph[nodeIndex]) // Duyệt qua tất cả member trong node có nodeIndex đó ví dụ: nodeIndex =0 => graph[0] = [1,3]  thì ta lần lượt lấy v = 1, rồi v = 3.
                    {
                        /*
                            nhờ ràng buộc của đề (node chỉ có value từ 0 đến n-1), ta không lo bị vượt index khi code dùng v cho duyệt index trong array_check_node[v].
                            Nếu input không tuân thủ ràng buộc (node chỉ có value từ 0 đến n-1) thì mới có nguy cơ lỗi, nhưng trong bài toán này input luôn hợp lệ.
                        */
                        if (array_check_node_color[v] == -1) //code dòng này nghĩa là, khi ta đang đứng ở 1 node bất kỳ ví dụ đang là  graph[0] = [1,3]. ta kiểm tra array_check_node = [0,-1,-1,-1].array_check_node[1] = -1
                        {
                            // gán màu ngược lại
                            array_check_node_color[v] = 1 - array_check_node_color[nodeIndex];// hết for thì  array_check_node_color sẽ như vậy.  array_check_node_color= [0, 1, 0, 1]

                            queueNode_index.push(v);//push v vào queue để while chạy tiếp check node kế tiếp.
                        }
                        else if (array_check_node_color[v] == array_check_node_color[nodeIndex]) //RÀO CẢNG FALSE đồ thị bipartite. chính là đồ thị có thể chia thành 2 nhóm mà cạnh chỉ nối giữa 2 nhóm, không nối trong cùng nhóm.
                        {
                            // phát hiện cạnh nối 2 node cùng màu lúc này . color = [0, 1, 1, 1]
                            return false;
                        }

                        /*
                            Giả sử ta có đồ thị: graph = [[1,3],[0,2],[1,3],[0,2]]
                            Các cạnh: (0–1), (0–3), (1–2), (2–3).

                            Bắt đầu: tô node 0 màu đỏ (0).   Bắt đầu: node 0 → màu 0 . color = [0, -1, -1, -1]

                            Node 1 và 3 kề với 0 → tô màu xanh (1).    Node 1 và 3 kề với 0 → màu 1 .  color = [0, 1, -1, 1]

                            Node 2 kề với 1 và 3 → tô màu đỏ (0).  Node 2 kề với 1 và 3 → màu 0 .   color = [0, 1, 0, 1]


                            Kết quả: {0,2} màu đỏ, {1,3} màu xanh.
                            Không có cạnh nào nối hai node cùng màu → bipartite.

                            Đồ thị bipartite chính là đồ thị có thể chia thành 2 nhóm mà cạnh chỉ nối giữa 2 nhóm, không nối trong cùng nhóm.

                            👉 Kết quả cuối cùng:

                            Nhóm màu 0 = {0,2}

                            Nhóm màu 1 = {1,3}
                            Không có cạnh nào nối hai node cùng màu → bipartite.

                            ------------------------------------------------
                            Giả sử ta có đồ thị: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
                            Các cạnh: (0–1), (0–2), (0–3), (1–2), (2–3).

                            Bắt đầu: tô node 0 màu đỏ. Bắt đầu: node 0 → màu 0 .  color = [0, -1, -1, -1]

                            Node 1,2,3 → màu xanh. Node 1,2,3 kề với 0 → màu 1 . color = [0, 1, 1, 1]

                            Nhưng cạnh (1–2) nối hai node cùng màu xanh → vi phạm. Nhưng cạnh (1–2) nối hai node cùng màu (cả hai đều màu 1) → vi phạm.
                            → Không bipartite.

                            Đồ thị bipartite chính là đồ thị có thể chia thành 2 nhóm mà cạnh chỉ nối giữa 2 nhóm, không nối trong cùng nhóm.


                            ======================
                            giống giống với việc 3d mesh clear trong đồ họa
                            Trong đồ họa 3D, một mesh được tạo từ các đỉnh (vertices) và cạnh (edges), rồi ghép thành mặt (faces). Khi mesh “clear” hay “manifold”, tức là các cạnh và mặt được tổ chức hợp lý, không bị chồng chéo hay lặp lại.

                            Đồ thị bipartite cũng có tinh thần tương tự:

                            Ta chia các đỉnh thành hai tập hợp rời nhau (giống như chia vertices thành hai nhóm).

                            Các cạnh chỉ nối từ nhóm này sang nhóm kia, không nối trong cùng nhóm (giống như mesh không bị “chồng cạnh” trong một mặt).

                            Nếu xuất hiện chu trình lẻ (tam giác, ngũ giác…), thì giống như mesh bị “lỗi topological” → không thể phân chia thành hai nhóm hợp lệ.

                            Liên hệ trực quan:
                            Mesh sạch, manifold → cấu trúc rõ ràng, không lỗi → giống đồ thị bipartite.

                            Mesh lỗi, có cạnh chồng chéo → không thể phân nhóm vertices hợp lý → giống đồ thị không bipartite.
                        */
                    }
                }
            }
        }
        return true;
    }
};