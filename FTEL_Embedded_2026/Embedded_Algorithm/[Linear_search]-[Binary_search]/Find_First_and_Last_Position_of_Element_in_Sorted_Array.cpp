#include <vector>
using namespace std;

class Solution {
public:

    /*
    cho một array đã xắp xếp nums = [5,7,7,8,8,10], tìm ra vị trí đầu tiên và vị trí cuối cùng của giá trị con số 8

    Ý tưởng là ta sẽ viết hai hàm tìm kiếm nhị phân riêng biệt:
        - Một hàm tìm chỉ số 8 đầu tiên (left bound) của target. findFirst: mỗi lần thấy target thì vẫn tiếp tục dịch sang trái để tìm vị trí đầu tiên.
        - Một hàm tìm chỉ số 8 cuối cùng (right bound) của target. findLast: mỗi lần thấy target thì vẫn tiếp tục dịch sang phải để tìm vị trí cuối cùng.
    */

    //findFirst: mỗi lần thấy target thì vẫn tiếp tục dịch sang trái để tìm vị trí đầu tiên.
    //nums = [5,7,7,8,8,10], target = 8 → ans = 3
    /*
       khởi đầu : left = 0, right = 5 ans = -1
       Vòng while 1: mid = (0+5)/2 = 2, nums[2] = 7
                    So sánh: 7 >= 8 → sai → đi nhánh else → left = 2 + 1 = 3
                    Trạng thái: left = 3, right = 5

        Vòng while 2: mid = (3+5)/2 = 4, nums[4] = 8
                    So sánh: 8 >= 8 → đúng → right = 4 - 1 = 3
                    Trạng thái: left = 3, right = 3, do nums[4] == target là 8 => ans = 4

        Vòng while 3: mid = (3+3)/2 = 3, nums[3] = 8
                    So sánh: 8 >= 8 → đúng → right = 3 - 1 = 2
                    Trạng thái: left = 3, right = 2, do nums[3] == target là 8 => ans = 3 đè lên ans trước đó là 4
        kết thúc:
            Điều kiện left <= right không còn đúng (3 <= 2 sai) → thoát vòng lặp.
            Trả về ans = 3.
    */
    int findFirst(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int ans = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
            if (nums[mid] == target)
                ans = mid;
        }
        return ans;
    }

    //findLast: mỗi lần thấy target thì vẫn tiếp tục dịch sang phải để tìm vị trí cuối cùng. Nó là đối ngược lại của hàm findFirst
     //nums = [5,7,7,8,8,10], target = 8 → ans = 4
    /*
       Khởi tạo: left = 0, right = 5, ans = -1

         Vòng 1:
            mid = (0+5)/2 = 2 → nums[2] = 7,  7 <= 8 → đúng → left = 3,  nums[2] != target → ans = -1
            Trạng thái: left = 3, right = 5

        Vòng 2:
            mid = (3+5)/2 = 4 → nums[4] = 8,  8 <= 8 → đúng → left = 5,  nums[4] == target → ans = 4
            Trạng thái: left = 5, right = 5, ans = 4

        Vòng 3:
            mid = (5+5)/2 = 5 → nums[5] = 10,  10 <= 8 → sai → right = 4,  nums[5] != target → ans = 4 giữ nguyên
            Trạng thái: left = 5, right = 4

        Kết thúc:
            left <= right không còn đúng → thoát vòng lặp.
            Trả về ans = 4.
    */
    int findLast(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int ans = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
            if (nums[mid] == target)
                ans = mid;
        }
        return ans;
    }

    //hàm ghép lại trả ra kết quả  starting và ending position của số 8.
    vector<int> searchRange(vector<int>& nums, int target)
    {
        int start = findFirst(nums, target);
        int end = findLast(nums, target);
        return { start, end };
    }
};