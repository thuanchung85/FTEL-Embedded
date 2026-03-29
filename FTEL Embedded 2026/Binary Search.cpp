#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    //cho một array đã sắp xếp từ nhỏ tới lớn nums = [-1,0,3,5,9,12]
    //tìm số 9 trả ra index của nó
    //nếu không có thì trả ra -1
    int search(vector<int>& nums, int target)
    {
        //Khởi tạo hai biến left = 0, right = nums.size() - 1.
        int left = 0, right = nums.size() - 1;

        //while sẽ chạy cho tới khi giá trị index của biến left và right bằng hay vượt qua nhau
        while (left <= right)
        {
            int mid = left + (right - left) / 2; // tránh tràn số

            //nếu giá trị của phần tử tại ví trí mid == 9
            if (nums[mid] == target)
            {
                return mid;//nếu tìm thấy số 9 thì trả ra luôn.
            }
            //nếu số ở giữa mà có giá trị nhỏ hơn 9 thì đẩy left index  = mid + 1, cắt bỏ một khúc dư thừa phía bên trái mid, vì mid đã nhỏ hơn 9 thì bên trái mid chắc chắn cũng vậy
            else if (nums[mid] < target)
            {
                left = mid + 1;
            }
            //còn nếu mid > 9 thì,  dịch index của right về vị trí mid và trừ đi 1, cắt bỏ các phần tử bên phải mid vì mid lơn hơn 9 nên càng nằm bên phải mid thì càng lớn hơn 9
            else
            {
                right = mid - 1;
            }
            /*
            Với nums = [-1,0,3,5,9,12], target = 9:
            mid đầu tiên là 2 → nums[2] = 3 < 9 → dịch trái sang phải.
            mid tiếp theo là 4 → nums[4] = 9 → tìm thấy, trả về 4.
            */
        }


        return -1;//nếu hết while mà không thấy gì thì trả ra -1
    }
};