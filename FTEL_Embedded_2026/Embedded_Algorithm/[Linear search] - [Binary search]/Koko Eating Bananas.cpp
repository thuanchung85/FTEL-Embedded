#include <vector>
using namespace std;


class Solution {
public:

    /*
    - Có n đống chuối (piles). Mỗi đống có số lượng chuối khác nhau, được cho trong mảng piles[i]. piles = [3,6,7,11]
    - Koko có thể chọn một tốc độ ăn k (chuối/giờ).
    - Mỗi giờ, Koko chọn một đống chuối và ăn đúng k quả từ đống đó. Nếu đống đó có ít hơn k quả, Koko ăn hết số còn lại rồi nghỉ luôn trong giờ đó (không ăn thêm từ đống khác).
    - Koko muốn ăn chậm nhất có thể nhưng vẫn phải ăn hết tất cả chuối trước khi lính gác quay lại sau h giờ.
    - Nhiệm vụ: tìm giá trị nhỏ nhất của k sao cho Koko ăn hết toàn bộ chuối trong vòng h giờ.

    Ví dụ:
       ta có số chuối, nải 3 chuối, nải 6 chuối, nải 7 chuối, nải 11 chuối => piles = [3,6,7,11], cần ăn hết trong h = 8 giờ
        ==> cần tìm tốc độ ăn chuối cần phải có để ăn hết trong 8 giờ.

        ta giả sử:
            -> Nếu Koko ăn với tốc độ k = 4:

                    Đống 3 → ăn hết trong 1 giờ.

                    Đống 6 → cần 2 giờ (mỗi giờ ăn 4, rồi 2).

                    Đống 7 → cần 2 giờ (4 + 3).

                    Đống 11 → cần 3 giờ (4 + 4 + 3).

                    Tổng cộng = 8 giờ → vừa khít.

            -> Nếu Koko ăn với tốc độ k = 3 thì tổng giờ > 8, không kịp. → Đáp án: k = 4.

    */

    /*
    Ý Tưởng là :
    Tốc độ nhỏ nhất có thể: 1.

    Tốc độ lớn nhất có thể: max(𝑝𝑖𝑙𝑒𝑠)(ăn hết pile lớn nhất trong 1 giờ).

    Ta dùng Binary Search trên khoảng [1,max(𝑝𝑖𝑙𝑒𝑠)]:

    Với mid = (low + high)/2, tính tổng giờ cần.

    Nếu tổng giờ <= h → có thể giảm tốc độ → high = mid.

    Ngược lại → cần tăng tốc độ → low = mid + 1.

    Kết quả cuối cùng là low. k sẽ bằng low.
    */

    //hàm này nhận giá trị mid thay vào int k để check trả ra true hay fasle nếu mid đó thõa mãn là số giờ ăn hết chuối
    bool canFinishEatBananaIn_h_hours(vector<int>& piles, int h, int k)
    {
        long long hours = 0;//tạo biến hours 

        for (int bananas : piles) //truền bananas = 3, =6, =7, =11
        {
            hours += (bananas + k - 1) / k; // ceil(bananas/k)
            if (hours > h)
                return false;
        }
        return hours <= h;

        /*
        Giả sử h = 8.

        Trường hợp k = 4
        Đống 3: (3+4-1)/4 = 6/4 = 1 giờ

        Đống 6: (6+4-1)/4 = 9/4 = 2 giờ

        Đống 7: (7+4-1)/4 = 10/4 = 2 giờ

        Đống 11: (11+4-1)/4 = 14/4 = 3 giờ
        → Tổng = 1+2+2+3 = 8 giờ → canFinish = true.

        Trường hợp k = 3
        Đống 3: (3+3-1)/3 = 5/3 = 1 giờ

        Đống 6: (6+3-1)/3 = 8/3 = 2 giờ

        Đống 7: (7+3-1)/3 = 9/3 = 3 giờ

        Đống 11: (11+3-1)/3 = 13/3 = 4 giờ
        → Tổng = 1+2+3+4 = 10 giờ > 8 → canFinish = false.

        Trường hợp k = 5
        Đống 3: (3+5-1)/5 = 7/5 = 1 giờ

        Đống 6: (6+5-1)/5 = 10/5 = 2 giờ

        Đống 7: (7+5-1)/5 = 11/5 = 2 giờ

        Đống 11: (11+5-1)/5 = 15/5 = 3 giờ
        → Tổng = 1+2+2+3 = 8 giờ → canFinish = true.

        =========
        Với k = 3 → không kịp (10 giờ).
        Với k = 4 → vừa khít (8 giờ).
        Với k = 5 → cũng kịp (8 giờ).
        Nhưng vì ta cần tốc độ nhỏ nhất do code trong loop while tiếp tục tìm kiếm nhỏ hơn → đáp án là k = 4. chứ không phải 5, khi while tìm ra số 5 nó vẩn thấy chạy tiếp được và tìm ra số 4 tối ưu hơn.
        */
    }

    int minEatingSpeed(vector<int>& piles, int h)
    {
        int left = 1; // là giờ tối thiểu là 1 
        int right = *max_element(piles.begin(), piles.end());//số giờ tối đa cần ăn chuối, cũng chính là phần tử max trong array. Kiếm ra phần tử lớn nhất trong array ví dụ [3,6,7,11] => max là 11

        //ta chay while Binary Search để kiếm ra số giờ tối thiểu khác lớn hơn 1 và nhỏ hơn 11 hợp lý hơn để ăn hết chuối. Và nó là 4 giờ nếu theo array  [3,6,7,11]
        while (left < right)
        {
            //tìm giá trị mid nằm giữa left và right.
            int mid = left + (right - left) / 2;

            if (canFinishEatBananaIn_h_hours(piles, h, mid)) //check coi với giá trị mid hiện tại thì vẫn chạy ok hàm canFinish, suy ra ta có thể tính tiếp xem còn có mid khác tốt hơn không? nghĩa là mid có thể còn có giá trị nhỏ hơn nữa vẫn ok.
            {
                right = mid; // thử giảm tốc độ
            }
            else //nếu mid mà truyền vào hàm canFinish trả ra false thì có nghĩa là mid này vẫn còn chậm, ta có thể dịch left lên để kiếm gia trị mid khác tốt hơn. cần tìm mid có giá trị lớn hơn để ăn kịp hàm canFinishEatBananaIn_h_hours
            {
                left = mid + 1; // cần tăng tốc độ
            }
        }

        return left;
    }
};