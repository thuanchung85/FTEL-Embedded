#include <vector>
using namespace std;

class Solution {
    //cho array có các số từ 0 .... đến n
    //Input: nums = [9,6,4,2,3,5,7,0,1]
    //Output là số bị thiếu chính là số 8: 8
public:
    int missingNumber(vector<int>& nums)
    {
        int n = nums.size();//n là số lượng các phần tử trong array

        //Tổng các số từ 0 đến n là: tính từ [0,1,2,3,4,5,6,7,8,9] => 45
        int expectedSum = n * (n + 1) / 2;

        //duyệt for để cộng tất cả các phần tử trong array lại nums = [9,6,4,2,3,5,7,0,1] => 37
        int actualSum = 0;
        for (int num : nums) {
            actualSum += num;
        }

        //suy ra giá trị số bị thiếu là 45 - 37 = 8
        return expectedSum - actualSum;
    }
};