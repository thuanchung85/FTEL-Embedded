#include <vector>
#include <iostream>
using namespace std;
class Solution {
    /*
    Ý tưởng: Ta cần tìm phần tử thứ 3 có giá trị lớn nhất khác nhau trong mảng.
    Nếu không đủ 3 giá trị khác nhau trong array thì trả về giá trị lớn nhất.
    Yêu cầu O(n): nghĩa là ta chỉ
    duyệt mảng một lần, không được sort toàn bộ.

    nums = [3,2,1]
    Các số khác nhau: 3, 2, 1.
    Lớn nhất: 3, lớn nhì: 2, lớn ba: 1.→ Kết quả: 1.

    nums = [1,2]
    Các số khác nhau: 2, 1.
    Chỉ có 2 số distinct, không đủ 3.→ Trả về số lớn nhất: 2.

    nums = [2,2,3,1]
    Các số khác nhau: 3, 2, 1.
    Lớn nhất: 3, lớn nhì: 2, lớn ba: 1.→ Kết quả: 1.

    nums = [3,2,1,4,1]
    Các số khác nhau: 4, 3, 2, 1.
    Lớn nhất: 4, lớn nhì: 3, lớn ba: 2.→ Kết quả: 2.
    */
public:
    int thirdMax(vector<int>& nums) {
        // long long: đây là kiểu số nguyên 64-bit trong C++, LLONG_MIN là giá
        // trị nhỏ nhất có thể của kiểu đó.
        long long max1 = LLONG_MIN, max2 = LLONG_MIN, max3 = LLONG_MIN; // Dùng 3 biến để lưu max1, max2, max3 (lần lượt là số lớn nhất, lớn nhì, lớn ba).

        // duyệt qua hết array nums
        for (int x : nums) {
            cout << "Xét phần tử: " << x << endl;

            if (x == max1 || x == max2 || x == max3) {
                cout << "  Bỏ qua vì trùng lặp" << endl;
                continue;// nếu có phần tử trung lặp với giá trị đã có trong max1, max2, max3, thì cỏ thể bỏ qua phần tử đó để chạy tiếp for với x khác.
            }

            // trường hợp này quan tâm tới max1, đẩy x  vào max1, dịch giá trị max1 củ về max2, và max2 về max3.
            if (x > max1) {
                max3 = max2;
                max2 = max1;
                max1 = x;
                cout << "  Cập nhật if MAX1 : max1=" << max1 << ", max2=" << max2
                    << ", max3=" << max3 << endl;
            }

            // trường hợp này quan tâm tới max2, đẩy x vào max2, dịch giá trị max2 củ về max3.
            else if (x > max2) {
                max3 = max2;
                max2 = x;
                cout << "  Cập nhật else if MAX2 : max1=" << max1
                    << ", max2=" << max2 << ", max3=" << max3 << endl;
            }

            // trường hợp này quan tâm tới max3 , đẩy vào max3
            else if (x > max3) {
                max3 = x;
                cout << "  Cập nhật else if MAX3 : max1=" << max1
                    << ", max2=" << max2 << ", max3=" << max3 << endl;
            }
        }

        cout << "Kết quả cuối cùng: ";
        //nếu max3 mà chưa bi tác động giá trị thì có nghĩa là array chỉ có 2 hay nhiều phần tử có giá trị khác nhau vậy trả ra phần tử giá trị to lớn nhất 
        if (max3 == LLONG_MIN)
        {
            cout << max1 << " (không đủ 3 distinct)" << endl;
            return max1;
        }
        //nếu max3 có giá trị mới add vào thì lấy giá trị max3 ra dùng.
        else
        {
            cout << max3 << endl;
            return max3;
        }
    }
};