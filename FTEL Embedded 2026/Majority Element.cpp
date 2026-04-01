#include <vector>
using namespace std;

class Solution {
public:
    //cho một array có chiều dài là n. Tìm ra số nào xuất hiện nhiều lần nhất, tức là phần tử chiếm đa số. 
    //Phần tử chiếm đa số là phần tử xuất hiện nhiều hơn ⌊n / 2⌋ lần.  theo công thức [n/2]

    /*
    Ta duyệt qua mảng, giữ một biến candidate (ứng viên cho majority element) và một biến count.
    Nếu count == 0, ta gán candidate = nums[i].

    Nếu phần tử hiện tại bằng candidate, tăng count. Ngược lại, giảm count.

    Sau khi duyệt hết mảng, candidate chính là majority element (do đề bài đảm bảo tồn tại).

    VD: Với nums = [3,2,3]:
        candidate = 3, count = 1 → gặp 2 thì count giảm → gặp 3 thì count tăng → cuối cùng candidate = 3.

    VD: Với nums = [2,2,1,1,1,2,2]:
        candidate cuối cùng là 2, đúng với majority element.

    VD:  Với mảng [3,2,3,4,6,4] thì thuật toán Boyer–Moore Majority Vote sẽ chạy được,
    nhưng kết quả không đảm bảo đúng vì trong mảng này không tồn tại majority element (không có phần tử nào xuất hiện nhiều hơn ⌊n/2⌋ = 3 lần).
    ta thấy n = 6 => 6/2 = 3, tức phải có phần tử xuất hiện 3 lần trong array.
    */
    int majorityElement(vector<int>& nums)
    {
        int candidate = 0, count = 0;

        //Ta duyệt qua mảng, giữ một biến candidate (ứng viên cho majority element) và một biến count.
        for (int num : nums)
        {
			if (count == 0) //chạy lần đầu khi count == 0, đây còn gọi là bước “chọn ứng viên mới” vì khi count = 0 thì ta sẽ gán candidate = num, tức là chọn num làm ứng viên mới.
            {
                candidate = num;//mới vô gắn candidate = num
            }

            //sau đó tăng giảm count theo lựa chọn logic đôi là nếu num = candidate thì cộng còn ngược lại thì trừ.
            /*
            ví dụ nếu array = [3,2,3,4,6,4,3]: array này thỏa n =7 => n/2 = 3, mà có số 3 trong array đúng 3 lần.
                Bắt đầu: candidate = 3, count = 1

                Gặp 2: khác candidate → count = 0

                Vì count = 0 → reset: candidate = 3, count = 1

                Gặp 4: khác candidate → count = 0

                Reset: candidate = 6, count = 1. count ở đây là reset lại vì bắt gặp số 6 là số mới . khi gặp 6 thì không phải tăng count, mà là do trước đó count = 0 nên ta reset         candidate = 6, count = 1. Đây là bước “chọn ứng viên mới” chứ không phải tăng count cho ứng viên cũ.

                Gặp 4: khác candidate → count = 0

                Reset: candidate = 3, count = 1

                Gặp 3: bằng candidate → count = 2

                ->  Kết quả cuối cùng: candidate = 3.

            */
            count += (num == candidate) ? 1 : -1;
        }

        //trả ra candidate
        return candidate;
    }
};