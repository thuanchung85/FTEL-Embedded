#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
    //cho một chuổi có các giá trị toàn dương ví du: nums = [10,2] => ghép lại thành giá trị cao nhất có thể và convert nó ra chuổi string => "210"
    //nums = [3,30,34,5,9] => "9534330"
public:
    string largestNumber(vector<int>& nums)
    {
        // Chuyển các số thành chuỗi
        //ví du nums = {3, 30, 34, 5, 9} => arr = {"3", "30", "34", "5", "9"}
        vector<string> arr;
        for (int num : nums) {
            arr.push_back(to_string(num));//convert số thành ký tự và push vào array dạng string.
        }

        // Sắp xếp với comparator tùy chỉnh
        // gọi hàm sort sắp xếp của C++ để sắp xếp toàn bộ vector arr.
        sort(
            arr.begin(),
            arr.end(),
            [](const string& a, const string& b) {
                //Nếu khi ghép a rồi b (chuỗi a+b) lớn hơn khi ghép b rồi a (chuỗi b+a), thì a phải đứng trước b.
                /* ví dụ:
                a = "3", b = "30". => a+b = "330", b+a = "303".
                So sánh "330" với "303", ta thấy "330" lớn hơn.
                → Vậy "3" phải đứng trước "30" trong kết quả cuối cùng.

                Quy ước so sánh chuỗi trong C++
                C++ dùng lexicographical order (thứ tự từ điển).
                Nó so sánh từng ký tự từ trái sang phải theo mã ASCII (hoặc Unicode nếu dùng chuẩn mở rộng).
                Khi gặp ký tự khác nhau đầu tiên, kết quả so sánh được quyết định bởi giá trị mã của ký tự đó.
                Nếu một chuỗi là tiền tố của chuỗi kia (ví dụ "abc" và "abcd"), thì chuỗi ngắn hơn được coi là nhỏ hơn.

                ví du: "330" vs "303" → so sánh ký tự đầu tiên: '3' == '3', ký tự thứ hai: '3' > '0' → "330" lớn hơn.

                ví dụ: "95" vs "59" → ký tự đầu tiên '9' > '5' → "95" lớn hơn.
                */
                string ab = a + b;
                string ba = b + a;
                cout << "So sánh: a = " << a << " và b = " << b
                    << " ->  check: ab = " << ab << " có lớn hơn > ba = " << ba
                    << "  => kết quả  " << (ab > ba ? "true => chọn a(" + a + ") trước b(" + b + ")" : "false => chọn b(" + b + ") trước a(" + a + ")")
                    << endl;
                return ab > ba;


            } //đây là lambda function dùng làm comparator, tức là quy tắc so sánh giữa hai phần tử. return a + b > b + a;: chính là quy tắc so sánh. 

        );

        cout << "Kết quả sau sắp xếp: ";
        for (auto& s : arr) cout << s << " ";
        cout << endl;


        // Nếu số lớn nhất là "0" thì kết quả chỉ là "0".Trả về "0" nếu phần tử đầu tiên sau sắp xếp là "0" (tránh kết quả như "0000").
        if (arr[0] == "0") return "0";


        // Ghép các chuỗi lại
        string result;
        for (auto& s : arr)
        {
            result += s;
        }
        return result;
    }
};