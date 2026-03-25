#include <vector>
using namespace std;

class Solution {
    // Ý tưởng là ta cần sắp xếp mảng gồm các số 0, 1, 2 mà không dùng hàm sort có sẵn.
    //nums = [2,0,2,1,1,0] Output: [0,0,1,1,2,2]
    //nums = [2,0,1] Output: [0,1,2]
public:
    void sortColors(vector<int>& nums)
    {
        /*
        Dùng ba con trỏ index vị trí các phần tử trong array:
            low: vị trí index tiếp theo để đặt số 0.
            mid: con trỏ đang duyệt.
            high: vị trí index tiếp theo để đặt số 2.
        */
        int low = 0, mid = 0, high = nums.size() - 1;

        //chạy while khi mà con trỏ index mid vẫn còn co thể chạy tiếp nó còn <= con trỏ high 
        while (mid <= high)
        {
            if (nums[mid] == 0) //nếu con trỏ mid mà nhận giá trị = 0, thì swap với con trỏ low index để con trỏ low ghi nhận giá trị 0, tức là giá trị thấp nhất.
            {
                swap(nums[low], nums[mid]);
                low++;// khi low nhận giá trị 0 thì ta yên tâm là nó có giá trị thấp nhất rồi, nên đẩy nó tiến lên vị trí index tiếp theo.
                mid++;//đẩy con trỏ mid tiếp theo sau low.
            }
            else if (nums[mid] == 1)
            {
                mid++;
            }
            else // nếu nums[mid] == 2 thì đẩy con số 2 này về chổ index của con trỏ high, tức là cuối array 
            {
                swap(nums[mid], nums[high]);// lúc này con trỏ index mid sẽ nhận giá trị nhỏ hơn hoặc = 2 sau khi swap 
                high--;// dịch con trỏ index high cuối array về trái 1 bậc , tức là đang chiếu vào số kế cuối.
            }

            /*nums = [2,0,2,1,1,0]
                low = 0, mid = 0, high = 5 ==> [0,0,2,1,1,2] => low = 0, mid = 0, high = 4
                low = 0, mid = 0, high = 4 ==> [0,0,2,1,1,2] => low = 1, mid = 1, high = 4
                low = 1, mid = 1, high = 4 ==> [0,0,2,1,1,2] => low = 2, mid = 2, high = 4
                low = 2, mid = 2, high = 4 ==> [0,0,1,1,2,2] => low = 2, mid = 2, high = 3
                low = 2, mid = 2, high = 3 ==> [0,0,1,1,2,2] => low = 2, mid = 3, high = 3
                low = 2, mid = 3, high = 3 ==> [0,0,1,1,2,2] => low = 2, mid = 4, high = 3 ==> kết thúc while do: mid > high.
            */
        }
    }
};