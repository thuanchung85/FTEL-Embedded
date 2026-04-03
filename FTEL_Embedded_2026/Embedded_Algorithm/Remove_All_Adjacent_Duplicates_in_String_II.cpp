#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    //cho chuổi s = "deeedbbcccbdaa" và một số k = 3
    //xóa chuổi cho tới khi không còn 3 ký tự giống nhau trong chuổi
    /*
        First delete "eee" and "ccc", get "ddbbbdaa"
        Then delete "bbb", get "dddaa"
        Finally delete "ddd", get "aa"
    */
    string removeDuplicates(string s, int k)
    {
        // Stack lưu pair<char, count>
        // dùng stack để lưu ký tự và số lần xuất hiện liên tiếp của nó.
        stack<pair<char, int>> st;

        //Duyệt qua từng ký tự trong chuỗi s
        for (char c : s)
        {
            //Với mỗi ký tự, nếu nó giống ký tự trước đó (trên đỉnh stack), ta tăng số lần xuất hiện lên.
            if (!st.empty() && st.top().first == c)
            {
                st.top().second++;//cộng thêm 1 vào số lần xuất hiện của ký tự
                if (st.top().second == k) //nếu nó == 3 thì xóa nó
                {
                    st.pop(); // xóa nhóm k ký tự
                }
            }
            //Với mỗi ký tự, nếu nó chưa có trong stack thì push vào stack, và gắn cho nó giá trị 1
            else
            {
                st.push({ c, 1 });
            }
        }

        // Ghép lại chuỗi từ stack
        string result;
        while (!st.empty()) {
            auto [ch, cnt] = st.top();
            st.pop();
            result.append(cnt, ch);
        }

        //do chuổi ghép từ stack sẽ bị ngược, nên ta đảo chuổi lại
        reverse(result.begin(), result.end());
        return result;
    }
};