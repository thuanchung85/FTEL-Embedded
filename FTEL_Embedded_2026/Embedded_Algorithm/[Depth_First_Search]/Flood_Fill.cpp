#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /*
        cho 1 matrix = [
                        [1,1,1],
                        [1,1,0],
                        [1,0,1]
                        ]

        -cho vị trí r và c, tức là row và column ta tìm ra vị trí ô cần xữ lý trong matrix
        -cho giá trị color = 2 , ta sẽ thay đổi toàn bộ giá trị các ô mà liền kề với ô có vị trí r,c theo 4 hướng lên xuống trái phải ->  thành giá trị 2

        ví dụ:  ô[1,1] = 1 => giá trị mới cần bỏ vào là color = 2
        => ta có matrix new =  [
                        [2,2,2],
                        [2,2,0],
                        [2,0,1]
                        ]
            ô = 0 thì không bị tác động
            ô[2,2] = 1, không có liền kề theo 4 hướng với ô  ô[1,1] nên không bị tác động.
    */

    void Depth_First_Search(vector<vector<int>>& image, int row_ThisSquare, int column_ThisSquare, int newColor, int oldColor)
    {
        //số hàng và cột của matrix
        int m = image.size();
        int n = image[0].size();

        // nếu r và c của ô cần xữ lý, truyền vào nằm ngoài số hàng và số cột của matrix thì không hợp lệ, end hàm
        if (row_ThisSquare < 0 || row_ThisSquare >= m || column_ThisSquare < 0 || column_ThisSquare >= n) return;

        //Dòng này đảm bảo ta chỉ tô màu những ô pixel liên thông với điểm xuất phát và có cùng màu như nhau.Nếu không có điều kiện này, thuật toán sẽ tô lan sang cả những pixel màu khác, làm sai kết quả.
        //đây chính là điều kiện dừng trong hàm đệ quy (DFS), 
        //ví dụ : khi mà ta chạm vào một ô mà giá trị của nó là 0, thì hồi trước oldColor của mình đang là 1, mà chạy đến ô này nó lại có giá trị = 0, vậy ta biết là mình bước qua lãnh thổ của nước khác rồi, end hàm.
        //khi ta đang đi trong “lãnh thổ” màu 1, mà gặp một ô màu 0 thì coi như đã bước sang đất nước khác, không cùng màu gốc nữa → kết thúc nhánh duyệt.
        if (image[row_ThisSquare][column_ThisSquare] != oldColor) return;

        //nếu 1 ô nào mà pass hết 2 vòng if trên thì nó sẽ bị đổi màu, thay giá trị mới từ 1 sang newcolor là 2
        image[row_ThisSquare][column_ThisSquare] = newColor;

        // đệ quy lại với các ô lân cận 4 hướng, trên dưới trái phải. Depth_First_Search duyệt 4 hướng
        Depth_First_Search(image, row_ThisSquare + 1, column_ThisSquare, newColor, oldColor);
        Depth_First_Search(image, row_ThisSquare - 1, column_ThisSquare, newColor, oldColor);
        Depth_First_Search(image, row_ThisSquare, column_ThisSquare + 1, newColor, oldColor);
        Depth_First_Search(image, row_ThisSquare, column_ThisSquare - 1, newColor, oldColor);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color)
    {
        int oldColor = image[sr][sc];//lấy giá trị màu của ô chỉ định làm nền tản cho biến oldColor, oldColor sẽ không thay đổi trong suốt quá trình chạy Depth_First_Search

        if (oldColor == color) return image; // không cần đổi nếu color cần thay đổi cũng trùng màu giá trị với ô hiện có.

        Depth_First_Search(image, sr, sc, color, oldColor);//truyền vào hàm Depth_First_Search: matrix, vị trí ô chỉ định, giá trị color mới, giá trị oldColor 

        return image;
    }
};