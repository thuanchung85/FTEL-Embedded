#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /*
        cho 1 matrix = [
        ["1","1","0","0","0"],
        ["1","1","0","0","0"],
        ["0","0","1","0","0"],
        ["0","0","0","1","1"]
    ]

        => tính ra các hòn đảo hợp thành bởi số 1 , các số 1 sẽ kết nối theo 4 hướng trên dưới trái phải, không tính đường chéo, suy ra ta có 3 đảo


    */
    //HÀM CON: Depth_First_Search, hàm này chạy theo nguyên lý là, nếu tìm ra 1 vị trí là đất liền trên matrix thì cứ ăn mòn lần lượt cho hết các ô đất liền xung quanh mà nó có giá trị 1. giống như xụp đất liên tục cho đến khi hòn đảo biến mất.
    //rồi ta duyệt matrix tìm hòn đảo nạn nhân tiếp theo.
    void Depth_First_Search(vector<vector<char>>& grid, int i, int j)
    {
        int m = grid.size();//biến số hàng matrix => 4
        int n = grid[0].size();//biến số cột matrix => 5

        // Kiểm tra biên hoặc gặp nước thì dừng, tức là i, j phải chạy từ 0 - hàng, và 0 - cột, ô grid[i][j] hiện tại phải khác 0. Nếu không thỏa các điều đó thì end hàm.
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0') return;

        // nếu pass qua if trên, thì có nghĩa là  grid[i][j hiện tại đang xet là = 1, chắc chắn là đất liền. Ta đánh dấu ô này thành nước để không duyệt lại
        grid[i][j] = '0';

        // từ vị trí i, j hiện tại, ta tiếp tục check thêm 4 ô liền kề. Trên , dưới, trái phải.
        Depth_First_Search(grid, i + 1, j);
        Depth_First_Search(grid, i - 1, j);
        Depth_First_Search(grid, i, j + 1);
        Depth_First_Search(grid, i, j - 1);
    }

    //HÀM MAIN
    int numIslands(vector<vector<char>>& grid)
    {
        if (grid.empty()) return 0;// nếu matrix rổng thì return 0
        int m = grid.size();// lấy ra số hàng matrix
        int n = grid[0].size();// lấy ra số cột matrix
        int count = 0;// số lượng đảo , (các ô có giá trị 1).

        //chạy for duyệt hết hàng matrix
        for (int i = 0; i < m; i++)
        {
            //chạy for duyệt hết cột matrix
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1') //nếu ô nào = 1, thì tăng count số đảo lên 1
                {
                    count++;
                    Depth_First_Search(grid, i, j);// hàm này cần truyền vào matrix, số hàng hiện tại đang chạy, và số cột hiện tại đang chạy.
                }
            }
        }
        return count;
    }
};