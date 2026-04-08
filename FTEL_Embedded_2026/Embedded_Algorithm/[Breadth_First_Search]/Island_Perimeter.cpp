#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /*
        Bạn được cho một lưới dài rộng là x và y. Trong đó grid[i][j] = 1 đại diện cho đất liền và grid[i][j] = 0 đại diện cho nước.
        chiều rộng và chiều cao không vượt quá 100. Xác định chu vi của đảo. Đảo không có hồ con và biển không có đảo khác nữa.
    */

    int islandPerimeter(vector<vector<int>>& grid)
    {
        int rows = grid.size(); // biến ghi lại số hàng của matrix
        int cols = grid[0].size(); // biến ghi lại số cột của mỗi hàng trong matrix
        int perimeter = 0; //biến ghi chu vi đảo.

        //duyệt matric theo từng hàng.
        for (int i = 0; i < rows; i++)
        {
            //duyện mỗi cột của mỗi hàng.
            for (int j = 0; j < cols; j++)
            {
                //ta đem từng ô trong matrix ra kiểm tra. 4 mặt nếu có mặt nào mà giáp biển thì cộng 1 vào chu vi đảo.
                /* Với mỗi ô đất (grid[i][j] == 1), ta kiểm tra 4 hướng.
                Nếu hướng đó đi ra ngoài biên (i == 0, i == rows-1, j == 0, j == cols-1) hoặc là nước (grid[...] == 0), thì cộng thêm 1 vào chu vi.
                */
                if (grid[i][j] == 1)
                {
                    // kiểm tra 4 hướng
                    // trên
                    if (i == 0 || grid[i - 1][j] == 0)
                        perimeter++;
                    // dưới
                    if (i == rows - 1 || grid[i + 1][j] == 0)
                        perimeter++;
                    // trái
                    if (j == 0 || grid[i][j - 1] == 0)
                        perimeter++;
                    // phải
                    if (j == cols - 1 || grid[i][j + 1] == 0)
                        perimeter++;
                }
            }
        }
        return perimeter;
    }
};