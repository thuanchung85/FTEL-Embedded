#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    //Cho một chuổi trong đó có thể chứa ký tự lỗi ví dụ: "leEeetcode", fix nó thành leetcode, bằng cách loại bỏ "E"
    string makeGood(string s)
    {
        stack<char> st;
        /*
        Ngăn xếp Stack là một cấu trúc dữ liệu tuyến tính hoạt động theo nguyên tắc LIFO (Last In First Out),
        nghĩa là các phần tử được đưa vào ngăn xếp cuối cùng sẽ là phần tử đầu tiên được lấy ra khỏi ngăn xếp.
        */

        //chạy duyệt hết string s
        for (char c : s)
        {
            //abs(st.top() - c) == 32: vì trong bảng ASCII, ký tự thường và ký tự hoa của cùng một chữ cái chênh nhau đúng 32. Dùng stack để dễ dàng loại bỏ các cặp ký tự "bad".
            //nếu phát hiện ra c là chữ hoa thì so với st.top tức là phần tử đầu tiên của stack coi nó trùng không 
            //hàm top() sẽ trả về phần tử nằm ở đỉnh của stack (phần tử được thêm vào cuối cùng).
            if (!st.empty() && abs(st.top() - c) == 32)
            {
                // Nếu ký tự hiện tại và ký tự trên cùng khác nhau đúng 32, nghĩa là khác biệt giữa chữ thường và chữ Hoa là 32 điểm
                // (chênh lệch giữa 'a' và 'A')
                st.pop(); //thì remove ký tự c đó 
            }

            //nếu c là ký tự bình thường thì add vào stack st
            else
            {
                st.push(c);
            }
        }

        //khai báo chuổi sẽ trả ra sau khi lọc lại
        string result;

        //duyệt stack st nếu nó có phần tử, thì di chuyển dần dần các phần tủ vào string result và xóa ra khỏi stack st
        while (!st.empty())
        {
            result.push_back(st.top());
            st.pop();
        }

        //do sau khi di chuyển từ stack về chuổi string thì các ký tự bị đảo ngược . nên ta phải reverse string lại một lần nữa.
        reverse(result.begin(), result.end());

        return result;
    }
};