#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    /*
    cho ma trận Input:
    mat = [[0,0,0],
           [0,1,0],
           [1,1,1]]

        hãy check từng phần tử trong ma trận và ghi ra số bước mà đi từ phần tử đó đến phần tử có giá trị 0 gần nhất. không được đi đường chéo. chỉ đi ngang hay dọc.
        ví dụ:
            mat[0][0] = 0 => giá trị 0 gần nó nhất là chính nó. = 0
            mat[0][1] = 0 => giá trị 0 gần nó nhất là chính nó. = 0
            mat[0][2] = 0 => giá trị 0 gần nó nhất là chính nó. = 0

            mat[1][0] = 0 => giá trị 0 gần nó nhất là chính nó. = 0
            mat[1][1] = 1 => giá trị 0 gần nó nhất là  3 đứa mat[0][1] , mat[1][0], mat[1][2] => tốn 1 bước
            mat[1][2] = 0 => giá trị 0 gần nó nhất là chính nó. = 0

            mat[2][0] = 1 => giá trị 0 gần nó nhất là 1 đứa mat[1][0] = 0 => tốn 1 bước
            mat[2][1] = 1 => giá trị 0 gần nó nhất là 2 đứa mat[1][0], mat[1][2] = 0 => tốn 2 bước , do không được đi chéo.
            mat[2][2] = 1 => giá trị 0 gần nó nhất là 1 đứa mat[1][2] = 0 => tốn 1 bước

    cho nên ma trận Output sẽ ghi lại là:
    [[0,0,0],
     [0,1,0],
     [1,2,1]]


    bài này quen quen, mình có dùng nó để làm thuật toàn tìm đường đi cho 1 nhân vật từ điểm A đến điểm B trong matrix, nhưng mà nó cực kỳ chậm và tốn kém. mình nghe nói có giải thuật Jump gì gì đó
    giải thuật “Jump Point Search” (JPS) là một tối ưu hóa của A dành cho bản đồ dạng lưới, giúp tìm đường nhanh hơn bằng cách bỏ qua các ô trung gian và chỉ xét những “điểm nhảy” quan trọng.* Nó thường được dùng trong game hoặc mô phỏng khi nhân vật cần di chuyển từ A đến B trên grid.

    Jump Point Search là gì?
    Xuất phát từ A: A vốn là giải thuật tìm đường phổ biến, nhưng trên lưới lớn thì phải duyệt rất nhiều node.

    Ý tưởng chính của JPS: thay vì duyệt từng ô một, JPS “nhảy” qua các ô liên tiếp theo một hướng cho đến khi gặp:

    Một ô bắt buộc phải rẽ (forced neighbor).

    Hoặc ô đích.

    Kết quả: giảm số lượng node cần duyệt, nhưng vẫn đảm bảo tìm được đường đi ngắn nhất.

    >>>>>>>>>>>>ý tưởng của bài này là:<<<<<<<<<<<<<<<
    Trong toàn bộ giải thuật này ta có 3 thực thể chính:

    Ma trận gốc mat: Đây là dữ liệu đầu vào, chứa các giá trị 0 và 1.Nó không thay đổi trong quá trình chạy, chỉ dùng để biết ô nào là nguồn (0) và ô nào cần tính khoảng cách (1).

    Hàng đợi q: Đây là cấu trúc dữ liệu dùng cho BFS. Ban đầu chứa tất cả tọa độ của các ô bằng 0. Sau đó, mỗi lần BFS lan ra một ô mới thì ô đó được đưa vào queue để tiếp tục xử lý. Queue đảm bảo BFS lan theo lớp (layer), nên khoảng cách luôn đúng và tối ưu.

    Ma trận kết quả dist: Ban đầu toàn bộ là -1. Các ô bằng 0 trong mat được gán thành 0 trong dist. Các ô bằng 1 sẽ được BFS cập nhật dần thành khoảng cách ngắn nhất đến số 0. Đây chính là output cuối cùng.

    */

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
    {
        int m = mat.size(), n = mat[0].size(); // tạo 2 biến ghi lại số hàng và số cột của matrix

        vector<vector<int>> dist(m, vector<int>(n, -1)); // tạo một matrix m hàng, và n cột, toàn bộ có giá trị -1, dist = [[-1,-1,-1],[-1,-1,-1],[-1,-1,-1]]

        /*
        queue là cấu trúc dữ liệu FIFO (First-In-First-Out) → phần tử nào vào trước sẽ được xử lý trước.
        Khi ta khởi tạo BFS, ta đưa tất cả các ô có giá trị 0 vào queue. pair<int,int> lưu tọa độ (i, j) của một ô trong ma trận.
        */
        queue<pair<int, int>> queue_IndexOf_CheckMember;

        // Bước 1: đưa tất cả ô 0 của matrix vào queue_IndexOf_CheckMember, ghi lại tọa độ index của nó.
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 0)
                {
                    dist[i][j] = 0; // => dist = [[0,0,0],[0,-1,0],[-1,-1,-1]]
                    queue_IndexOf_CheckMember.push({ i,j }); // ta có thể hình dung là queue_IndexOf_CheckMember =[{0,0}, {0,1}, {0,2}, {1,0}, {1.2}]
                }
            }
        }


        // ta tạo ra 2 array hằng số dx và dy, mục đích là để phục vụ cho dòng for chạy trong while code bên 
        /*
        dx và dy là hai mảng song song. Khi duyệt, ta dùng chỉ số k từ 0 đến 3 để lấy ra một cặp (dx[k], dy[k]).
        Cụ thể:
           k=0: (dx[0], dy[0]) = (1,0) → đi xuống (x+1, y).
           k=1: (dx[1], dy[1]) = (-1,0) → đi lên (x-1, y).
           k=2: (dx[2], dy[2]) = (0,1) → đi sang phải (x, y+1).
           k=3: (dx[3], dy[3]) = (0,-1) → đi sang trái (x, y-1).

           =>Nhờ cách viết này, ta chỉ cần một vòng lặp for (int k=0; k<4; k++) là duyệt được cả 4 hướng, thay vì phải viết 4 câu lệnh riêng biệt.
        */
        vector<int> dx = { 1,-1,0,0 };
        vector<int> dy = { 0,0,1,-1 };

        // Bước 2: BFS, while còn chạy nếu queue_IndexOf_CheckMember còn phần tử trong đó, 
        //while này có tác dụng là lôi từng đứa trong queue_IndexOf_CheckMember ra các số (0) -> rồi check với 4 hướng xung quanh số 0 đó. nếu phát hiện ra gần nó có ô nào chứa -1 thì bỏ vào ô đó +1 điểm. sau đó Đưa ô đó vào queue để BFS tiếp tục lan từ nó ra.
        while (!queue_IndexOf_CheckMember.empty())
        {
            //đem phần tử đầu queue_IndexOf_CheckMember ra xữ lý.
            int x = queue_IndexOf_CheckMember.front().first;
            int y = queue_IndexOf_CheckMember.front().second;

            queue_IndexOf_CheckMember.pop();//remove nó đi, queue_IndexOf_CheckMember cứ remove từng phần tử trong mổi lần while, nếu pop hết thì end while.

            for (int k = 0; k < 4; k++) //dòng for chạy k từ 0 -> 3 để truy cập (dx , dy)
            {
                // đem giá trị (index) x, và y của từng phần tử trong queue_IndexOf_CheckMember ra tính toán với dx va dy để ra indexOf_near_x và indexOf_near_y. tức là vị trí các ô kế bên nó theo 4 hướng nhìn.
                int indexOf_near_x = x + dx[k];
                int indexOf_near_y = y + dy[k];

                if (indexOf_near_x >= 0 && indexOf_near_x < m) //→ kiểm tra chỉ số hàng indexOf_near_x nằm trong phạm vi ma trận (0 đến m-1).Nếu indexOf_near_x < 0 hoặc indexOf_near_x ≥ m thì ô đó nằm ngoài ma trận → bỏ qua.
                {
                    if (indexOf_near_y >= 0 && indexOf_near_y < n)// → kiểm tra chỉ số cột indexOf_near_y nằm trong phạm vi ma trận (0 đến n-1).Nếu indexOf_near_y < 0 hoặc indexOf_near_y ≥ n thì ô đó nằm ngoài ma trận → bỏ qua.
                    {
                        if (dist[indexOf_near_x][indexOf_near_y] == -1) // → kiểm tra ô (indexOf_near_x, indexOf_near_y) chưa được thăm. Vì ban đầu ta gán tất cả bằng -1, sau đó khi BFS lan tới ô nào thì ta gán khoảng cách cho nó. Nếu dist[indexOf_near_x][indexOf_near_y] != -1 nghĩa là ô đó đã có khoảng cách rồi, không cần xử lý lại.
                        {
                            dist[indexOf_near_x][indexOf_near_y] = dist[x][y] + 1;
                            queue_IndexOf_CheckMember.push({ indexOf_near_x,indexOf_near_y });
                        }
                    }
                }
            }
        }

        return dist;
    }
};