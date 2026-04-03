#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
    //kiểm tra array , nếu trong array có các phần tử mang giá trị giống nhau thì trả ra true, còn tất cả khác nhau thì trả ra false.
    //[1,2,3,1] => true, có 2 số 1 trùng nhau
    //[1,2,3,4] => false, Tất cả khác nhau

public:
    //Ta cần kiểm tra xem trong mảng có phần tử nào xuất hiện ít nhất 2 lần hay không.
    bool containsDuplicate(vector<int>& nums)
    {
        //Dùng unordered_set: duyệt qua từng phần tử, nếu phần tử đã tồn tại trong set thì trả về true. Nếu duyệt hết mà không trùng thì trả về false.
        //unordered_set Nó lưu trữ các phần tử không trùng lặp (unique).
        unordered_set<int> seen;

        for (int num : nums)
        {
            // kiểm tra xem phần tử num có nằm trong set seen hay không.
            if (seen.count(num))
            {
                return true; // đã thấy num trước đó
            }

            //bỏ từng phần tử num của array vào set seen
            seen.insert(num);
        }
        return false; // không có phần tử trùng
    }
};