#include <vector>
#include <string>
#include <stack>
using namespace std;

class Solution {
    //cho 1 array dạng tokens = ["2","1","+","3","*"]
    //biến nó thành công thức toán.
    //và trả ra giá trị.
public:
    int evalRPN(vector<string>& tokens)
    {
        //Dùng stack để lưu các toán hạng. + ,  - , * , /
        //stack là dạng FILO
        stack<int> st;

        //Duyệt qua từng phần tử trong mảng tokens:
        for (string& t : tokens)
        {
            //Nếu là toán tử (+, -, *, /) → pop 2 phần tử trên cùng của stack (chú ý thứ tự):
            /*
            Giả sử lấy b = st.top() rồi pop, sau đó a = st.top() rồi pop.
            Tính a op b (với op là toán tử).
            Push kết quả trở lại stack.
            */
            if (t == "+" || t == "-" || t == "*" || t == "/")
            {
                int b = st.top();
                st.pop();
                int a = st.top();
                st.pop();

                int res = 0;
                if (t == "+")
                    res = a + b;
                else if (t == "-")
                    res = a - b;
                else if (t == "*")
                    res = a * b;
                else if (t == "/")
                    res = a / b; // chia nguyên, tự động truncate về 0
                st.push(res);
            }
            //Nếu là số → push vào stack.
            else
            {
                st.push(stoi(t)); // chuyển string thành int,
            }

            /*
            Input: ["2","1","+","3","*"]
            Quá trình:
                Push 2, push 1 → stack [2,1]
                Gặp + → lấy 2+1=3, push → stack [3]
                Push 3 → stack [3,3]
                Gặp * → lấy 3*3=9, push → stack [9]
                Output: 9
            */
        }

        //Sau khi duyệt hết, kết quả cuối cùng nằm ở st.top()
        return st.top();
    }
};