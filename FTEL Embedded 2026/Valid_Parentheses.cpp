#include <string>
#include <stack>
using namespace std;

class Solution {
public:

    //Hàm kiểm tra chuổi
    //ý tưởng là ta cần 1 stack để chứa ký tự và dùng nó để so với từng phần tử trong chuỗi input, nếu 2 ký tự hợp với nhau thì ok, và chạy tiếp, nếu bất kỳ lúc nào mà fail thì return luôn.
   //ví dụ: string input là s = "([)]"
   //Ban đầu stack trống: st = []
   // Vòng lặp duyệt từng ký tự trong chuỗi s.
   //Lần 1: c = '('
   //Đây là dấu ngoặc mở → đẩy vào stack. Stack: st = ['(']
   //Lần 2: c = '['
   //Cũng là ngoặc mở → push vào stack. Stack: st = ['(', '[']
   //Lần 3: c = ')'
   //Đây là ngoặc đóng. Kiểm tra stack có rỗng không → không rỗng. Lấy phần tử trên cùng: top = '['. Pop ra khỏi stack. Stack sau pop: ['(']
   // Kiểm tra: c == ')' nhưng top = '[' → không khớp. Kết quả: return false ngay tại đây.
   //Hàm trả về false vì chuỗi "([)]" không hợp lệ.

   /*Nếu chạy với s = "([])":
    ( → push → stack = ['(']

    [ → push → stack = ['(', '[']

    ] → pop '[' → khớp ,bỏ qua làm tiếp ký tự khác → stack = ['(']

    ) → pop '(' → khớp ,bỏ qua làm tiếp ký tự khác → stack = []

    Hết vòng lặp → stack rỗng → return true.*/

    bool isValid(string s)
    {
        //(<stack>). Ngăn xếp hoạt động theo nguyên tắc LIFO (Last In, First Out) – phần tử được đưa vào sau cùng sẽ được lấy ra trước.
        stack<char> st;

        //với mỗi ký tự trong chuỗi s, gán ký tự đó vào biến c. Mỗi lần lặp, sẽ xử lý một ký tự trong chuỗi.
        for (char c : s)
        {
            if (c == '(' || c == '{' || c == '[') //kiểm tra c có phải là dấu mở hay không? (, {, [
            {
                st.push(c);  // nhét c vào stack
            }
            else //kiểm tra c có phải là dấu đóng hay không? ), }, ] 
            {
                if (st.empty()) return false;  // nếu stack đang là empty thì thoát luôn khỏi chạy code dưới nữa.

                //nếu pass qua code check bên trên thì tức là stack có ít nhất 1 phần tử rồi, ta lấy phần tử top ra check, chính là phần tử cuối cùng đưa vào stack 
                char top = st.top();
                st.pop();//xóa phần tử trên cùng của stack đi 

                //kiểm tra top với c nếu không phải là 1 cặp của nhau thì thất bại 
                if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '['))
                {
                    return false;  // thất bại return fail luôn chuỗi không ok
                }
            }
        }

        return st.empty();  // nếu stack mà không chứa gì sau khi for chạy hết thì thành công chuổi đó OK 
    }



};