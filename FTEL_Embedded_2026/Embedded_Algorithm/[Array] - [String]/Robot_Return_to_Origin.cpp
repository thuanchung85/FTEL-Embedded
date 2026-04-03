#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    //nhập chuổi moves = "UD" vào cho chương trình robot, robot sẽ di chuyển theo tương ứng "U đi lên", "D đi xuống", "L đi qua trái", "R đi qua phải"
    // nếu chuổi lệnh moves sau khi chạy hết mà robot nằm ở vị trí 0,0 ban đầu thì true, còn lại là false 
    bool judgeCircle(string moves)
    {
        int x = 0, y = 0; // gắn x, y là tọa độ 0,0 gốc mà tại đó robot xuất phát 

        //duyệt từng ký tự trong chuổi moves 
        for (char c : moves)
        {
            //U: tăng y
            if (c == 'U')
                y++;

            //D: giảm y    
            else if (c == 'D')
                y--;

            //R: tăng x    
            else if (c == 'R')
                x++;

            //L: giảm x    
            else if (c == 'L')
                x--;
        }


        //nếu vị trí x, y cuối cùng sau khi hết for loop là 0,0 thì true, nếu khác thì false
        return x == 0 && y == 0;
    }
};