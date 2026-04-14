#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    /*
        cho một matrix grid = [[2,1,1],[1,1,0],[0,1,1]], số 2 nghĩa là có 1 quả cam thối ở đó,
        cứ mỗi 1 phút trôi qua, thì quả cam thối số 2 đó sẽ đánh vào 4 ô ở các hướng trên dưới trái phải.
        quả cam tươi nào nằm trong 4 ô đó sẽ chuyển thành thối, có giá trị = 2
        => tính ra số phút cần để cam thối chiếm hết matrix
        => nếu có quả cam tươi nào bị cách ly 4 hướng thì nó không thể bị cam thối chiếm tới, nên trả ra => số phút là -1, vì cam thối vĩnh viễn không thể chiếm hết matrix

    */

    int orangesRotting(vector<vector<int>>& grid)
    {
        int m = grid.size(); // số hàng matrix 
        int n = grid[0].size();// số cột matrix

        queue<pair<int, int>> queueCamThoi;// hàng đợi ghi lại ví trí hàng và cột của cam thối
        queue<int> timeQueue; // Nếu gặp cam tươi (1), ta biến nó thành cam thối (2) và đưa vào queue với thời gian +1. timeQueue này giống cuốn sổ note lại mốc thời gian các đợt cam thối hoành hành
        int freshCount = 0; //giữ nhiệm vụ đếm số lượng cam tươi còn lại trong lưới.


        int maxTime = 0;//lưu lại số phút lớn nhất cần thiết. để cam thối chiếm hết matrix

        int dirs[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };// array 2 chiều để áp dụng phép tính di chuyển của cam thôi ra 4 hướng, trên dưới trái phải. 
        /*{1,0}: đi xuống (tăng chỉ số hàng). {-1,0}: đi lên (giảm chỉ số hàng).
          {0,1}: đi sang phải (tăng chỉ số cột). {0,-1}: đi sang trái (giảm chỉ số cột).*/

          // duyệt qua hết các ô trong matrix, và đưa tất cả cam thối vào queueCamThoi và mỗi lần bóc được cam thối là ghi vào timeQueue
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //nếu ô matrix đó là = 2 vậy là cam thối
                if (grid[i][j] == 2)
                {
                    queueCamThoi.push({ i,j });// ghi lại ví trí index cam thối trong matrix vào queue để chạy while BFS
                    timeQueue.push(0);// khởi tạo timeQueue = {0}. queue này đóng vai trò lưu lại số phút (thời gian) mà một quả cam thối xuất hiện trong queue.  timeQueue này giống cuốn sổ note lại mốc thời gian các đợt cam thối hoành hành
                    //nó có dạng ví dụ timeQueue = [0,0,1,1...,2,..3]
                }
                //nếu ô matrix đó = 1, vậy là cam tươi
                else if (grid[i][j] == 1)
                {
                    freshCount++; // ghi lại số cam tươi có trong matrix, cộng vào freshCount
                }
            }
        }

        //chạy while các quả cam thối dùng thuật toàn BFS 
        while (!queueCamThoi.empty())
        {
            //bóc quả cam thối trong queueCamThoi ra xữ lý, cho nó hoạt động 
            int x = queueCamThoi.front().first;
            int y = queueCamThoi.front().second;
            queueCamThoi.pop();// xóa nó khỏi queueCamThoi 

            int t = timeQueue.front(); // bóc mốc thời gian của quả cam thối trên ra xữ lý
            timeQueue.pop();

            maxTime = max(maxTime, t);// gắn t vào maxtime, nếu maxtime này trước đó đã có giá trị thì so sánh để chọn ra giá trị lớn nhất.

            //duyệt for cho 4 phần tử 4 hướng đi lan truyền của cam thối. trên dưới trái phải
            for (auto& d : dirs)
            {
                //cặp biến nx, ny này là 1 trong 4 vị trí dự tính của các ô lân cận quả cam thối
                int nx = x + d[0];
                int ny = y + d[1];

                //check ô matrix ở vị trí nx, ny đó, nếu nó là cam tươi = 1 thì biến nó thành thối = 2
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1)
                {
                    grid[nx][ny] = 2; // biến thành cam thối, và -1 một cho biến cam tươi
                    freshCount--;

                    //Khi ta lấy ra (x, y) từ q, ta cũng lấy ra t từ timeQ. Nhờ vậy, khi lan sang các quả cam tươi xung quanh, ta biết được chúng sẽ thối ở phút t+1.
                    queueCamThoi.push({ nx,ny }); //bỏ cam thối vào queueCamThoi, để nó làm nguyên liệu cho thuật toán chạy tiếp BFS lan ra từ nó. 
                    timeQueue.push(t + 1);//ghi vào note lịch sữ timeQueue thời gian mà quả cam này đã thối. chính là t hiện tại + 1 phút.
                }
            }
        }

        return freshCount == 0 ? maxTime : -1; //Nếu freshCount == 0 → nghĩa là tất cả cam tươi đã bị thối, ta trả về số phút lớn nhất (maxTime).
    }
};