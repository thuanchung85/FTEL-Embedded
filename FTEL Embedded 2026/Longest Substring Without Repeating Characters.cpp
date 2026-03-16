#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    void printSet(const unordered_set<char>& st) {
        cout << "{ ";
        for (auto c : st)
            cout << c << " ";
        cout << "}" << endl;
    }

    // ví dụ s = "pwwkew", kiếm tra chuổi string con bên trong coi nó dài nhất
    // là bao nhiêu ký tự, chuổi string con không được có ký tự trùng lắp. The
    // answer is "wke", with the length of 3. Notice that the answer must be a
    // substring, "pwke" is a subsequence and not a substring.
    int lengthOfLongestSubstring(string s) {
        // khởi tạo các biến left = 0, maxLength = 0, charSet = {}.unordered_set
        // là một cấu trúc dữ liệu lưu các phần tử duy nhất, không trùng lặp.
        unordered_set<char> charSet;
        // Dùng unordered_set để lưu các ký tự trong cửa sổ hiện tại.
        // Con trỏ right duyệt qua chuỗi, nếu gặp ký tự trùng thì dịch left cho
        // đến khi loại bỏ được ký tự trùng. Luôn cập nhật độ dài lớn nhất
        // maxLength.
        int left = 0, maxLength = 0;

        /*right = 0 → 'p'
        'p' chưa có trong set → thêm vào. charSet = {p}  maxLength = max(0,
        0-0+1) = 1

        right = 1 → 'w'
        'w' chưa có → thêm vào. charSet = {p, w}  maxLength = max(1, 1-0+1) = 2

        right = 2 → 'w'
        'w' đã có trong set → chạy vòng while:

        Xóa s[left] = 'p', left = 1 → charSet = {w}

        'w' vẫn còn trong set → tiếp tục: xóa s[left] = 'w', left = 2 → charSet
        = {} Thêm 'w' mới vào → charSet = {w} maxLength = max(2, 2-2+1) = 2

        right = 3 → 'k'
        'k' chưa có → thêm vào.charSet = {w, k}  maxLength = max(2, 3-2+1) = 2

        right = 4 → 'e'
        'e' chưa có → thêm vào.charSet = {w, k, e}  maxLength = max(2, 4-2+1) =
        3

        right = 5 → 'w'
        'w' đã có → chạy vòng while:

        Xóa s[left] = 'w', left = 3 → charSet = {k, e}
        Thêm 'w' mới vào → charSet = {k, e, w}
        maxLength = max(3, 5-3+1) = 3
        */

        //chạy hết chuổi s = "pwwkew"
        for (int right = 0; right < s.size(); right++)
        {
            //cout << "Xét ký tự: " << s[right] << endl;

            //nếu khi chạy duyệt chuổi s mà có ký tự trùng thì while sẽ kích hoạt.
            while (charSet.find(s[right]) != charSet.end())
            {
                //cout << "  Bị trùng: " << s[right] << " → xóa " << s[left] << endl;
                charSet.erase(s[left]);
                left++; //chổ này biến left bị tác động làm cho nó tăng lên + 1, và window sẽ co rút lại bên trái, chi khi có event bị trùng ký tự diển ra 
                //cout << "  charSet sau khi xóa: ";
                //printSet(charSet);
            }

            //thêm ký tự đang duyệt vào charSet
            charSet.insert(s[right]);
            //cout << "  Thêm " << s[right] << " → charSet: ";
            //printSet(charSet);

            //thuật toán tạo khung cửa sổ, nó là 1 array chứa vị trí của ký tự trong chuổi s , kéo dài từ bên trái biến left đến bên phải biến right  
            maxLength = max(maxLength, right - left + 1);
            /*cout << "  Window [" << left << ", " << right
                 << "] → length = " << right - left + 1
                 << ", maxLength = " << maxLength << endl;
            cout << "-----------------------------" << endl;*/
        }

        return maxLength;
    }
};