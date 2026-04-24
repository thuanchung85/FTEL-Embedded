#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /* cho matrix
        isConnected = [[1,1,0],
                       [1,1,0],
                       [0,0,1]]
        ta có các phần tử gọi là các city ví dụ:: city1 = [1,1,0], city2 = [1,1,0], city3 = [0,0,1]

        xét city1 =  [1,1,0], có nghĩa là:  city1[0] = 1 => nghĩa là chính city 1 đó đang nối với chính nó
                                            city1[1] = 1 => nghĩa là chính city 1 đó đang nối với city2
                                            city1[2] = 0 => nghĩa là chính city 1 đó đang không nối với city3

        xét city2 =  [1,1,0], có nghĩa là:  city2[0] = 1 => nghĩa là chính city 2 đó đang nối với city1
                                            city2[1] = 1 => nghĩa là chính city 2 đó đang nối với chính nó
                                            city2[2] = 0 => nghĩa là chính city 2 đó đang không nối với city3

        xét city3 =  [0,0,1], có nghĩa là:  city3[0] = 0 => nghĩa là chính city 3 đó đang không nối với city1
                                            city3[1] = 0 => nghĩa là chính city 3 đó đang không nối với city2
                                            city3[2] = 1 => nghĩa là chính city 3 đó đang nối với chính nó

        vậy output number of provinces = 2, gồm city 1 + city 2 và city 3 đứng riêng.

        Ý tưởng DFS:
            - Duyệt qua tất cả các thành phố. Nếu thành phố chưa được thăm, ta chạy DFS từ nó để đánh dấu toàn bộ các thành phố liên thông với nó.
            - Mỗi lần bắt đầu DFS mới tức là tìm thấy một province mới.
            - Kết quả là số lần ta khởi chạy DFS.
    */

    //Nhiệm vụ của hàm Depth_First_Search chỉ là cố thay đổi giá trị của visited = {false,false,false} thành một dạng cuối cùng nào đó, để nhìn vào đó mô tả số  provinces, ví dụ khi chạy hết Depth_First_Search và các lần đệ quy. ta sẽ có visited = {false,false,false} chuyển thành visited = {true,true,false}, từ đó suy ra được  provinces = 2
    void Depth_First_Search(int u, vector<vector<int>>& isConnected, vector<bool>& visited)
    {
        visited[u] = true;//khi vào hàm thì thành phố ta truyền vào sẽ chuyển trang thái ngay từ false thành true, để đánh dấu là đã đi qua rồi.

        for (int v = 0; v < isConnected.size(); v++) //vì đề bài cho là matrix n x n, nên ta có thể dùng  isConnected.size() để chạy duyệt vòng for, for này chạy cho các  city1 = [1,1,0], city2 = [1,1,0], city3 = [0,0,1], duyệt các phần tử trong mỗi city đó như 1,1,0...0,0,1
        {
            if (isConnected[u][v] == 1 && !visited[v]) // nếu đọc thấy con số 1 từ phần tử [v] của isConnected[u](chính là city) và check visited[v] là false thì ta biết, ta đang kiểm tra mối nối tới từ city này tới các city lân cận, coi nó thế nào.
            {
                Depth_First_Search(v, isConnected, visited);// dựa trên con số v(con số của vị trí thành phố khác) để ta đệ quy check tiếp thành phố kế bên thành phố u này
            }
        }
    }

    //HÀM CHÍNH:
    int findCircleNum(vector<vector<int>>& isConnected)
    {
        int n = isConnected.size(); //số hàng của matrix, cũng là số cột matrix , cũng là số thành phố có thể kết nối từ 1 thành phố bất kỳ.
        vector<bool> visited(n, false); //visited chính là một mảng (array) kiểu bool có kích thước bằng số lượng city (n). Ban đầu tất cả phần tử đều là false. nghĩa là chưa có city nào được duyệt.


        int provinces = 0;//khởi tạo ban đầu cho provinces = 0

        for (int i = 0; i < n; i++) //duyệt hết các thành phố đang ghi nhận trong visited = {false,false,false}
        {
            if (!visited[i]) //nếu thành phố đó false, nghĩa là chưa được ghé thăm để check thì ta check thành phố đó
            {
                Depth_First_Search(i, isConnected, visited);//gọi giải thuật Depth_First_Search, truyền vào array visited = {false,false,false}, index của city đó chính là số i, và matrix isConnected

                //dòng provinces++ chỉ kích hoạt được một khi  Depth_First_Search(i, isConnected, visited) đã đệ quy xong, và lúc đó là 1 loạt các thành phố nối nhau đã bị đệ quy xúc đi sạch ta thấy qua thay đỗi của  visited
                /*
                    Ban đầu: visited = {false, false, false} (chưa thăm city nào).
                    Khi chạy DFS từ city1, nó sẽ thăm city1 và city2 vì chúng liên thông → visited = {true, true, false}. ->  provinces++ = 1;
                    Sau đó vòng lặp kiểm tra tiếp: city2 đã true nên bỏ qua.
                    Đến city3 thấy false, chạy DFS cho city3 → visited = {true, true, true}. ->  provinces++ = 2;

                    Mỗi lần bắt đầu DFS từ một city chưa thăm (visited[i] == false) thì tức là bạn vừa tìm thấy một province mới.
                */
                provinces++;
            }
        }
        return provinces;
    }
};