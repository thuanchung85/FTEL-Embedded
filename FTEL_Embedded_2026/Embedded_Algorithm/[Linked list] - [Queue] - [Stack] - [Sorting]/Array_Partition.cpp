#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    //cho 1 array nums = [1,4,3,2],
    //tách thành các trường hợp tạo cặp
    //trường hợp 1 => tách thành  (1, 4), (2, 3) 
    //trường hợp 2 => tách thành (1, 3), (2, 4) 
    //trường hợp 3 => tách thành (1, 2), (3, 4)
    //sau đó lấy min của các cặp và cộng lại
    //trường hợp 1 => min là 1, 2 => 3
    //trường hợp 2 => min là 1, 2 => 3
    //trường hợp 3 => min là 1, 3 => 4
    //return max là 4
public:
    int arrayPairSum(vector<int>& nums)
    {
        //Sắp xếp mảng nums.Sau khi sắp xếp: 1 2 3 4 
        sort(nums.begin(), nums.end());

        //Sau đó, lấy tổng của các phần tử ở vị trí chẵn (index 0, 2, 4, …).
        //Vì khi sắp xếp, việc ghép cặp liên tiếp sẽ đảm bảo giá trị nhỏ hơn trong mỗi cặp được tối đa hóa tổng thể.
        /*
        Sau khi sắp xếp, ta luôn ghép cặp (nums[0], nums[1]), (nums[2], nums[3]), …
        Trong mỗi cặp, phần tử nhỏ hơn chính là phần tử ở vị trí chẵn nums[0], nums[2], nums[4]...
        Do đó, chỉ cần cộng tất cả các phần tử ở vị trí chẵn là ra kết quả tối ưu.
        */
        int sum = 0;
        //duyệt array  nums = [1,2,3,4]
        for (int i = 0; i < nums.size(); i += 2) {
            sum += nums[i];
            /*
            Chọn phần tử ở vị trí 0 = 1
            Chọn phần tử ở vị trí 2 = 3
            Tổng cuối cùng = 4
            */
        }
        return sum;
    }
};