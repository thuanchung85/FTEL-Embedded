#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // cho chuổi S, tạo chuổi T từ chuổi S xáo trộn. Bỏ vào chuổi T một từ bất
    // kỳ và kiếm tra tìm ra từ được thêm đó
    /*Input: s = "abcd", t = "abcde"
    Output: "e"
    Explanation: 'e' is the letter that was added.
    */
    char findTheDifference(string s, string t) {
        /*XOR (^) có tính chất:

        x ^ x = 0 (một số XOR chính nó thì triệt tiêu).

        x ^ 0 = x.

        Thứ tự XOR không quan trọng (giao hoán, kết hợp).

        → Nghĩa là nếu ta XOR tất cả ký tự trong s và t, các ký tự giống nhau sẽ bị
        triệt tiêu, chỉ còn lại ký tự dư (chính là ký tự thêm vào).*/

        int result = 0;
        // chạy hết chuổi s và XOR từng ký tự trong đó
        for (char c : s)
            result ^= c;
        // chạy hết chuổi t và XOR từng ký tự trong đó
        for (char c : t)
            result ^= c;
        return char(result);

        /*
        Giả sử ta dùng biến result = 0.

        XOR tất cả ký tự trong s = "abcd":

        result = 0 ^ 'a' = 'a' (ASCII 97).

        result = 'a' ^ 'b'.

        result = ('a' ^ 'b') ^ 'c'.

        result = ((( 'a' ^ 'b') ^ 'c') ^ 'd').
        → Sau vòng này, result chứa một giá trị XOR của tất cả ký tự trong s.

        XOR tiếp với tất cả ký tự trong t = "abcde":

        Khi XOR với 'a', 'b', 'c', 'd' → chúng triệt tiêu với phần đã có từ s.

        Cuối cùng còn lại 'e' vì nó không có cặp để triệt tiêu.
        */
    }
};