#include <vector>
using namespace std;

class Solution {
    //cho một array có thứ tự tăng dần nums = [-4,-1,0,3,10]
    //lấy bình phương của tất cả các phần tử và tạo ra array mới [0,1,9,16,100]
public:
    /*
    Đặc điểm của mảng đầu vào. Mảng nums đã được sắp xếp tăng dần.
    Các số âm nằm bên trái, số dương nằm bên phải.

    Khi bình phương:
    Số âm lớn (ví dụ -7) có thể tạo ra số dương rất lớn (49).
    Số dương lớn (ví dụ 11) cũng tạo ra số lớn (121).
    Do đó, sau khi bình phương, thứ tự không còn giữ nguyên.
    */
    vector<int> sortedSquares(vector<int>& nums)
    {
        //Ta cần sắp xếp lại mảng sau khi bình phương. Thay vì bình phương xong rồi gọi sort() (O(n log n)), ta có thể lợi dụng tính chất mảng ban đầu đã sắp xếp.
        //ta so sánh ví dụ array [-4,-1,0,3,10]
        // ta lấy -4 so với 10 => [-4 * -4 = 16] < [10 * 10 = 100] => chọn 10 gắn vào  array result = [100], còn -4 thua nên đi đấu tiếp với 3
        // ta lấy -4 so với 3 => [-4 * -4 = 16] > [3 * 3 = 9] => chọn 16 gắn vào  array result =[16,100], còn 3 thua nên đi đấu tiếp với -1
        // ta lấy -1 so với 3 => [-1 * -1 = 1] < [3 * 3 = 9] => chọn 9 gắn vào  array result =[9,16,100], còn -1 thua nên đi đấu tiếp với 0
         // ta lấy -1 so với 0 => [-1 * -1 = 1] < [0 * 0 = 0] => chọn 1  gắn vào  array result =[1,9,16,100], còn lại 0 sẽ tự so với 0 => gắn vào array result 
         //kết quả = [0,1,9,16,100]
        int n = nums.size();
        vector<int> result(n);

        //Hai con trỏ index, Đặt left ở đầu mảng, right ở cuối mảng.
        int left = 0, right = n - 1;
        int pos = n - 1; // vị trí để điền số lớn nhất, vị trí này là vị trí cuối array.

        //while chạy để di chuyển 2 con trỏ bên trái và phải dần dần vào trung tâm
        while (left <= right)
        {
            //So sánh abs(nums[left]) và abs(nums[right]) giá trị tuyệt đối.
            //nếu bên trái lớn hơn
            if (abs(nums[left]) > abs(nums[right]))
            {
                //nhét giá trị bình phương của left vào array result tại vị trí cuối cùng.
                result[pos--] = nums[left] * nums[left];
                left++;// dịch left tới
            }
            //nếu bên phải lớn hơn hay bằng bên trái
            else
            {
                //nhét giá trị bình phương của right vào array result tại vị trí cuối cùng.
                result[pos--] = nums[right] * nums[right];
                right--;//dịch right về
            }
        }
        return result;
    }
};