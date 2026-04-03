#include <vector>
using namespace std;

class Solution {
public:

    //Mẹo là gộp các mảng ngay tại chỗ bên trong nums1, bắt đầu từ cuối để tránh ghi đè các phần tử chưa được xử lý.
    /*
    Bắt đầu
    p1 = m - 1 = 2 (trỏ vào phần tử 3 trong nums1)

    p2 = n - 1 = 2 (trỏ vào phần tử 6 trong nums2)

    p = m + n - 1 = 5 (vị trí cuối cùng trong nums1)

    Vòng lặp chính
    So sánh nums1[p1] = 3 và nums2[p2] = 6
    → 6 lớn hơn → đặt nums1[5] = 6
    → p2 = 1, p = 4
    nums1 = [1,2,3,0,0,6]

    So sánh nums1[p1] = 3 và nums2[p2] = 5
    → 5 lớn hơn → đặt nums1[4] = 5
    → p2 = 0, p = 3
    nums1 = [1,2,3,0,5,6]

    So sánh nums1[p1] = 3 và nums2[p2] = 2
    → 3 lớn hơn → đặt nums1[3] = 3
    → p1 = 1, p = 2
    nums1 = [1,2,3,3,5,6]

    So sánh nums1[p1] = 2 và nums2[p2] = 2
    → bằng nhau, theo code thì lấy từ nums2 → đặt nums1[2] = 2
    → p2 = -1, p = 1
    nums1 = [1,2,2,3,5,6]

    Kết thúc
    p2 đã < 0 → vòng lặp dừng.

    Không còn phần tử nào trong nums2 để copy thêm.

    Kết quả cuối cùng: [1,2,2,3,5,6]
    */

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;          //  con trỏ ghi lại vị trí cuối cùng của phần tử trong Array nums1 [1,2,3]
        int p2 = n - 1;          //  con trỏ ghi lại vị trí cuối cùng của phần tử trong Array nums2 [2,5,6]
        int p = m + n - 1;      // con trỏ ghi lại vị trí cuối cùng của phần tử trong Array kết quả cuối cùng nums1[1,2,3,0,0,0]

        // vòng lặp chạy nếu con trỏ của 2 mảng nums1 và nums2 còn dương, tức là còn hợp lệ.
        while (p1 >= 0 && p2 >= 0)
        {
            //So sánh nếu phần tử ở vị trí p1 của Array nums1 > phần tử ở vị trí p2 của Array nums2, 
            if (nums1[p1] > nums2[p2])
            {
                nums1[p] = nums1[p1]; //WIN lấy phần tử của Array nums1 bỏ vào Array kết quả cuối cùng nums1[1,2,3,0,0,0]
                p1--;//nums1 win nên được giảm con trỏ, giật về một đơn vị 
            }
            //nếu LOSE thì lấy phần tử của Array nums2
            else
            {
                nums1[p] = nums2[p2];
                p2--;//nums2 win nên được giảm con trỏ, giật về một đơn vị 
            }

            //mỗi lần while chạy xong là trừ p đi một điểm, để giật con trỏ dần dần về đầu Array nums1[1,2,3,0,0,0]
            p--;
        }

        // dùng cho trường hợp nums1 = [1], m = 1, nums2 = [], n = 0 và nums1 = [0], m = 0, nums2 = [1], n = 1
        while (p2 >= 0)
        {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
    }
};