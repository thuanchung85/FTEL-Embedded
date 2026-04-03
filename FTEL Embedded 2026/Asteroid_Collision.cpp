#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    /* Chúng ta được cho một mảng asteroids gồm các số nguyên đại diện cho các tiểu hành tinh theo một hàng.
     Chỉ số của tiểu hành tinh trong mảng biểu thị vị trí tương đối của chúng trong không gian.

    Đối với mỗi tiểu hành tinh, giá trị tuyệt đối đại diện cho kích thước của nó, và dấu hiệu đại diện cho hướng của nó (dương nghĩa là đi về bên phải, âm nghĩa là đi về bên trái).
    Mỗi tiểu hành tinh di chuyển với cùng một tốc độ.

    Hãy xác định trạng thái của các tiểu hành tinh sau tất cả các va chạm. Nếu hai tiểu hành tinh gặp nhau, tiểu hành tinh nhỏ hơn sẽ nổ. Nếu cả hai có cùng kích thước, cả hai sẽ nổ.
    Hai tiểu hành tinh di chuyển cùng hướng sẽ không bao giờ gặp nhau.

    ví dụ : [3,5,-6,2,-1,4]​​​​​​​
    Quá trình:
    -------------
    3,5 đi phải → stack [3,5]

    -6 đi trái → va chạm với 5 và 3, cả hai nổ → stack [-6]
    -----------------
    2 đi phải → stack [-6,2]

    -1 đi trái → va chạm với 2, 2 thắng → stack [-6,2]

    4 đi phải → stack [-6,2,4]
    */

    vector<int> asteroidCollision(vector<int>& asteroids)
    {
        stack<int> st;//dùng stack để lưu trạng thái các thiên thạch đang còn tồn tại

        //Duyệt lần lượt từng phần tử trong mảng asteroids.
        for (int a : asteroids)
        {
            bool alive = true;// mặc định giả sử default là các thiên thạch có số dương đi sang phải. để push vào stack st.

            //check từng thiên thạch a, Nếu thiên thạch a đi sang trái (giá trị số âm a < 0) → cần kiểm tra va chạm với các thiên thạch đang đi sang phải trong stack
            while (!st.empty() && a < 0 && st.top() > 0)
            {
                if (abs(a) > st.top()) //check giá trị với thiên thạch đang có trong stack top , nếu thắng thì hủy thiên thach của stack st. và chạy while tiếp 
                {
                    st.pop(); // thiên thạch đi phải nổ
                    continue;
                }
                //nếu giá trị của thiên thạch hiên tại a == với giá trị của thiên thạch top trong stack thì hủy cả hai
                else if (abs(a) == st.top())
                {
                    st.pop(); // cả hai cùng nổ
                }
                alive = false; // thiên thạch đi trái nổ
                break;// hủy while vì thiên thạch a đã die
            }

            //Nếu thiên thạch đang xét đi sang phải (số dương) → đưa vào stack.
            if (alive)
            {
                st.push(a);
            }

        }

        // chuyển stack thành vector kết quả
        vector<int> res(st.size());
        for (int i = st.size() - 1; i >= 0; --i)
        {
            res[i] = st.top();
            st.pop();
        }

        return res;
    }
};