#include <vector>
using namespace std;

class Solution {
public:
    /*cho 1 array Ví dụ: [0,1,2,4,5,6,7] , đem xoay nó theo thứ tự đầy phần tử cuối cùng lên đầu array.
            quá trình xoay như sau
            Nếu xoay 1 lần ta sẽ có → [7,0,1,2,4,5,6].
            Nếu xoay 2 lần → [6,7,0,1,2,4,5].
            Nếu xoay 3 lần → [5,6,7,0,1,2,4].
            Nếu xoay 4 lần → [4,5,6,7,0,1,2].

    Tìm ra số nhỏ nhất trong array trên.
    */
    // áp dụng binary search để tìm nhanh phần tử nhỏ nhất trong O(log n), thay vì phải duyệt hết.
    int findMin(vector<int>& nums)
    {

        int left = 0, right = nums.size() - 1;//Dùng hai biến left và right để giới hạn khoảng tìm kiếm.

        while (left < right)
        {
            //Tính mid. số ở giữa
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) // nếu giá trị số giữa > giá trị số bên phải, thì ta tăng left lên bằng số mid + 1, ta sẽ cắt bỏ được 1 đoạn bên left
            {
                // Min nằm ở bên phải
                left = mid + 1;
            }
            else // còn nếu giá trị số giữa < giá trị số bên phải, thì ta tăng right lên bằng số mid , ta sẽ cắt bỏ được 1 đoạn bên right
            {
                // Min nằm ở bên trái hoặc chính mid
                right = mid;
            }
            /*
            ví dụ array  [4,5,6,7,0,1,2]
            - lần 1: left = 0, right = 7 - 1 = 6, mid = 0 + (6 - 0)/2 = 3 . Tiếp => nums[3] = 7 > nums[6] = 2  ==> suy ra left = 3 +1 = 4
            - lần 2: left = 4, right = 6, mid = 4 + (6 - 4)/2 = 5 . Tiếp => nums[5] = 1 < nums[6] = 2 ==> suy ra right = 5
            - lần 3: left = 4, right = 5, mid = 4 + (5 - 4)/2 = 4 . Tiếp => nums[4] = 0 < nums[5] = 1 ==> suy ra right = 4
            - lần 4: left = 4, right = 4 => end while

            */
        }

        return nums[left];// trả ra nums[4] = 0
    }
};