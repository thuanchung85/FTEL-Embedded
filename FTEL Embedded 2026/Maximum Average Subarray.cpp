#include <vector>
using namespace std;
class Solution {
public:
    //Bạn được cho một mảng số nguyên nums gồm n phần tử, và một số nguyên k.  
    //Tìm một mảng con liền kề có độ dài bằng k có giá trị trung bình lớn nhất và trả về giá trị này.
    //Input: nums = [1,12,-5,-6,50,3], k = 4
    //Output: 12.75000
    double findMaxAverage(vector<int>& nums, int k) {

        double window_sum = 0.0; // Dùng biến window_sum để lưu tổng của cửa sổ hiện tại.

        // Tính tổng của k phần tử đầu tiên
        for (int i = 0; i < k; i++) {
            window_sum += nums[i];
        }
        //cout << "Lần Đầu window sum = " << window_sum << endl;

        double max_sum = window_sum; // ghi lại giá trị , tạm thời coi nó là max

        // Trượt cửa sổ ,chạy for từ phần tử thứ k cho tới hết array nums, mỗi lần trượt cửa sổ: trừ đi phần tử cũ, cộng thêm phần tử mới.
        for (int i = k; i < nums.size(); i++)
        {
            //cout << "trước khi dịch chuyển : window_sum = " << window_sum<< endl;
            //cout << "bỏ phần tử nums[" << i - k << "] = " << nums[i - k] << ", thêm phần tử nums[" << i << "] = " << nums[i] << endl;

            window_sum += nums[i] - nums[i - k]; // trừ đi phần tử cũ, cộng thêm phần tử mới.
            //cout << "sau khi dịch chuyển : window_sum = " << window_sum << endl;

            // Nếu thấy giá trị window_sum mới mà lớn hơn giá trị max_sum củ thì chọn làm giá trị max mới
            if (window_sum > max_sum) {
                //cout << "New max_sum found = " << window_sum << endl;
                max_sum = window_sum;
            }
        }

        return max_sum / k;// chia cho k để lấy giá trị trung bình.
    }
};