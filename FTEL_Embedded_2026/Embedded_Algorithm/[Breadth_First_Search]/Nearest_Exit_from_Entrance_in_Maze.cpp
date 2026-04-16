#include <iostream>
#include <queue>
using namespace std;

class Solution {
    /*
        - Cho matrix bản đồ game  maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], Trong đó phần tử "+" là tường, phần tử "." là sàn nhà.
        - Entrance = [1,2] là array chỉ ra vị trí bạn đang đứng trong ô matrix, ở đây là ô hàng 1, cột 2
        - Bạn có thể di chuyển theo 4 hướng, lên xuống trái phải. không thể đi ra khỏi matrix bản đồ, và không thể đi vào ô có tường.
        - Nhiệm vụ là bạn phải tìm ra đường đi ngắn nhất đến ô exit, là ô có ký tự "." tức là ô sàn nhà nằm ở rìa ngoài cùng bản đồ game. trả ra số lượng bước phải bước.
        - trả ra -1 nếu không có đường ra exit.
    */
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance)
    {
        //ghi lại số hàng và số cột của matrix bản đồ game
        //ví dụ: maze =[["+","+",".","+"],[".",".",".","+"],["+","+","+","."]] => m = 3, n = 4
        int m = maze.size();
        int n = maze[0].size();

        queue<pair<int, int>> q; //khởi tạo queue chứa các ô trong bản đồ game, vòng while sẽ check các ô trong queue này để xử lý giải thuật BFS

        vector<vector<int>> dist(m, vector<int>(n, -1));//sẽ tạo ra một ma trận 2 chiều có kích thước m x n (giống như maze), nhưng tất cả các phần tử ban đầu đều bằng -1.
        /*
            dist[i][j] dùng để lưu số bước ngắn nhất từ entrance đến ô (i,j). Ban đầu gán -1 để đánh dấu là chưa thăm.
            Khi BFS đi đến một ô (x,y), ta gán dist[x][y] = số bước từ entrance đến đó.
            Nhờ vậy, ta vừa kiểm soát được việc không đi lại ô đã thăm, vừa biết được khoảng cách ngắn nhất.
        */

        // Khởi queue tạo BFS từ entrance = [1,2]
        q.push({ entrance[0], entrance[1] }); //q=({1,2})

        /*đầu tiên gắn vị trí entrance[1,2] trong matrix dist thành 0 => dist =[["-1","-1","-1","-1"],
                                                                                ["-1","-1","0","-1"],
                                                                                ["-1","-1","-1","-1"]]

                                                            */
        dist[entrance[0]][entrance[1]] = 0;

        // 4 hướng di chuyển ta gắn vào 2 array để chạy for 1 lần duyệt cả 2 array và 4 hướng
        int dx[4] = { 1, -1, 0, 0 };
        int dy[4] = { 0, 0, 1, -1 };

        //vòng while chạy BFS khi queue còn phần tử ô cần check.
        while (!q.empty())
        {
            //lấy data từ phần tử ô matrix đầu tiên trong queue, chính là vị trí x là hàng, y là cột của ô đó.
            int x = q.front().first;
            int y = q.front().second;
            q.pop();//remove nó khỏi queue

            int stepsNeedExit = dist[x][y];//biến stepsNeedExit là biến số bước cần để thoát khỏi matrix

            // Kiểm tra nếu là exit (ở biên, khác entrance).Khối if dùng để kiểm tra xem ô hiện tại (x,y) có phải là exit hay không:
            if ((x == 0 || x == m - 1 || y == 0 || y == n - 1) && !(x == entrance[0] && y == entrance[1]))
            {
                return stepsNeedExit;// nếu ta đang đứng ở exit thì return kết quả stepsNeedExit luôn.
            }

            // Duyệt 4 hướng, check các vị trí 4 ô xung quanh ô ta đang ở x,y 
            for (int k = 0; k < 4; k++)
            {
                int nx = x + dx[k]; //biến vị trí hàng của 4 ô xung quanh
                int ny = y + dy[k]; //biến vị trí cột của 4 ô xung quanh

                //bước kiểm tra xem ô (nx, ny) có thể đi được hay không trước khi đưa nó vào hàng đợi BFS
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == '.' && dist[nx][ny] == -1)
                {
                    dist[nx][ny] = stepsNeedExit + 1;//nếu đi được thì tăng giá trị ô đó nx,ny trong matrix dist lên +1 đơn vị.
                    q.push({ nx, ny });//ta push ô vị trí ô nx, ny đó vào queue để while chạy tiếp trên ô nx,ny đó lan ra tiếp 4 ô nữa.

                    /*
                    Đặc trưng của BFS (Breadth-First Search) là duyệt theo từng “lớp” khoảng cách từ điểm xuất phát. Nghĩa là:
                    Đầu tiên nó duyệt tất cả các ô cách entrance 1 bước.
                    Sau đó đến các ô cách entrance 2 bước.
                    Rồi đến các ô cách entrance 3 bước…
                    Do đó, ngay khi BFS gặp một exit ở biên, thì chắc chắn đó là đường ngắn nhất để thoát ra. Không cần phải kiểm tra lại các ô khác nữa, vì BFS đảm bảo rằng ta đang duyệt theo thứ tự tăng dần số bước.
                    */
                }
            }
        }

        return -1; // Không tìm thấy exit
    }
};