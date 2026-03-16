#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    /*Cho hai chuỗi ransomNote và magazine, trả về true nếu ransomNote có thể được tạo bằng cách sử dụng các chữ cái từ magazine và trả về false nếu không.

    Mỗi chữ cái trong magazine chỉ có thể được sử dụng một lần trong ransomNote.
    ví du:
    Input: ransomNote = "aa", magazine = "aab"
    Output: true
    Input: ransomNote = "aa", magazine = "ab"
    Output: false*/
    /* ý tưởng là mapping chuổi magazine => count [0,0,.....0,0] có 26 phần tử, mãng này ghi lại số lần xuất hiện của các ký tự 'a' -> 'z' của chuổi magazine, và cộng thêm 1 giá trị vào các phần tử tương ứng:
    'a' xuất hiện trong magazine -> phần tử [0] của count + thêm 1
    'b' xuất hiện trong magazine -> phần tử [1] của count + thêm 1
    ...
    [z] xuất hiện trong magazine -> phần tử [25] của count + thêm 1
    */

    bool canConstruct(string ransomNote, string magazine) {
        // Mảng đếm số lần xuất hiện của các chữ cái trong magazine,dòng này tạo ra một vector gồm 26 số nguyên, tất cả đều bằng 0.
        //Ta dùng 26 phần tử này để đại diện cho 26 chữ cái trong bảng chữ cái tiếng Anh (a đến z).
        /*vector<int>: tạo một mảng động (vector) chứa các phần tử kiểu int.
        26: số lượng phần tử ban đầu trong vector là 26.
        0: giá trị mặc định để khởi tạo cho tất cả phần tử, tức là mỗi phần tử đều bằng 0.*/
        vector<int> count(26, 0);//[0,0,...,0,0]

        //duyệt chuổi magazine
        /*
            ví dụ magazine = "aab"
            Sau vòng lặp:
            count[0] = 2 (chữ 'a' xuất hiện 2 lần)
            count[1] = 1 (chữ 'b' xuất hiện 1 lần)
            các phần tử khác = 0
        */
        for (char c : magazine) {
            /*Ta dùng 'a' làm mốc vì:
                'a' là ký tự đầu tiên trong bảng chữ cái.
                Giúp ánh xạ các chữ cái từ 'a' đến 'z' thành chỉ số từ 0 đến 25.
                Phù hợp với mảng vector<int> count(26, 0); có 26 phần tử.
                'a' có mã ASCII là 97 , 'b' là 98 , 'z' là 122
                vậy:
                 dùng c - 'a' thì ?
                'a' - 'a' = 0 → ánh xạ vào count[0]
                'b' - 'a' = 1 → ánh xạ vào count[1]
                'z' - 'a' = 25 → ánh xạ vào count[25]

                 Nếu dùng c - 'b' thì sao?
                Giả sử c = 'b':

                'b' - 'b' = 0 → ánh xạ vào count[0]

                'c' - 'b' = 1 → ánh xạ vào count[1]

                'a' - 'b' = -1  → lỗi vì chỉ số âm!

                 Nếu dùng 'b' hay 'z' làm mốc thì các ký tự khác sẽ bị ánh xạ sai hoặc gây lỗi.
                */
            count[c - 'a']++;
            /*Gặp 'a' → count['a' - 'a'] = count[0]++ → count[0] = 1
                Gặp 'a' → count[0]++ → count[0] = 2
                Gặp 'b' → count['b' - 'a'] = count[1]++ → count[1] = 1
                count = [2, 1, 0, 0, ..., 0]  // 'a': 2 lần, 'b': 1 lần
            */
        }

        // Kiểm tra từng ký tự trong ransomNote = "aa"
        /*Gặp 'a' → count[0] = 2 → giảm còn 1
          Gặp 'a' → count[0] = 1 → giảm còn 0
          Không gặp lỗi → trả về true*/
        for (char c : ransomNote) {
            //nếu bất kỳ lúc nào mà kiểm tra thấy phần tử trong count có giá tri == 0 thì return false ngay 
            //ví du nếu ký tự c là ='f' thì lúc này code  count['f' - 'a'] = count[5] == 0 => false ngay lập tức 
            if (count[c - 'a'] == 0) {
                return false;
            }
            //code này làm giảm giá trị tại ví trí tương ứng với ký tự trong chuổi ransomNote
            /*'a' sẽ chạy đến phần tử [0] trong count đê trừ dần, nếu nó == 0 thì sẽ trả ra false ngay luôn, nếu pass qua mà không chạm vào == 0 thì tiếp tục cho tới hết chuổi*/
            count[c - 'a']--;
        }

        return true;//pass hết chuổi ransomNote, không bị chặn lại ở dòng for OK 
    }
};