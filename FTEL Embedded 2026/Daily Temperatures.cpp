#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    //cho một array [73,74,75,71,69,72,76,73], đó là số nhiệt độ theo từng ngày
    //tìm ra 1 array mới mà tại đó cho biết là còn bao nhiêu ngày nữa sẽ tới ngày ấm hơn
    /*
        [73] -> còn [1] ngày nữa là tới ngày ấm hơn, tức là ngày sau [74]
        [74] -> còn [1] ngày nữa là tới ngày ấm hơn, tức là ngày sau [75]
        [75] -> còn [4] ngày nữa là tới ngày ấm hơn, tức là ngày sau [76]
        [71] -> còn [2] ngày nữa là tới ngày ấm hơn, tức là ngày sau [72]
        [69] -> còn [1] ngày nữa là tới ngày ấm hơn, tức là ngày sau [72]
        [72] -> còn [1] ngày nữa là tới ngày ấm hơn, tức là ngày sau [76]
        [76] -> còn [0] ngày nữa là tới ngày ấm hơn, không có ngày sau ấm hơn
        [73] -> còn [0] ngày nữa là tới ngày ấm hơn, không có ngày sau ấm hơn

        ==> ta có array là [1,1,4,2,1,1,0,0]
    */
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        int n = temperatures.size();//biến n ghi lại kích thước của array temperatures
        vector<int> answer(n, 0);//khai báo array để lưu kết quả trả lời, có độ dài bằng array temperatures và đã init là 0 toàn bộ [0,0,0,0,0,0,0,0]

        /*
       Ngăn xếp Stack là một cấu trúc dữ liệu tuyến tính hoạt động theo nguyên tắc LIFO (Last In First Out),
       nghĩa là các phần tử được đưa vào ngăn xếp cuối cùng sẽ là phần tử đầu tiên được lấy ra khỏi ngăn xếp.
       */
        stack<int> st; // lưu chỉ số các ngày

        //chạy vòng lặp theo số lượng phần tử trong array temperatures [73,74,75,71,69,72,76,73]
        for (int i = 0; i < n; i++)
        {
            //while chỉ chạy khi stack có phần tử
            // so sánh nhiệt độ giá trị của 2 phần tử thứ [i] và thứ [st.top()] của array  [73,74,75,71,69,72,76,73], Nếu ngày hiện tại nóng hơn ngày ở đỉnh stack
            while (!st.empty() && temperatures[i] > temperatures[st.top()])
            {
                int prevDay = st.top();//save lại chỉ số index của ngày có nhiệt độ đã lưu trong stack st
                st.pop();//sau đó remove nó khỏi stack st

                answer[prevDay] = i - prevDay; // số ngày phải chờ
            }

            //push vị trí index của từng phần tử trong array [73,74,75,71,69,72,76,73] vào stack st
            st.push(i);

            /* ví dụ vector<int> temperatures = {73,74,75,71,69,72,76,73};
            Chạy qua hàm dailyTemperatures sẽ cho kết quả như sau:

            i = 0 (73): bỏ while do st empty, làm  st.push(i); st = [0] , answer[0,0,0,0,0,0,0,0]
            i = 1 (74): làm while do st có phần tử, temperatures[1] = 74 >  temperatures[0] = 73 ,  answer[0] = 1 - 0 => [1,0,0,0,0,0,0,0], pop st =[],  st.push(i); st =[1]

            i = 2 (75): làm while do temperatures[2] = 75 >  temperatures[1] = 74 ,  answer[1] = 2 - 1 => [1,1,0,0,0,0,0,0], pop st =[],  st.push(i); st =[2]
            i = 3 (71): bỏ while do  temperatures[3] = 71 <  temperatures[2] = 75,  st.push(i); st =[2,3]
            i = 4 (69): while bỏ qua vì 69 < 71 , st.push(4); st = [2,3,4], answer = [1,1,0,0,0,0,0,0]

            i = 5 (72): làm while vì 72 > 69
                        answer[4] = 5 - 4 = 1
                        pop st -> [2,3]
                        tiếp tục while: 72 > 71
                        answer[3] = 5 - 3 = 2
                        pop st -> [2]
                        72 < 75 nên dừng
                        st.push(5); st = [2,5]
                        answer = [1,1,0,2,1,0,0,0]

            i = 6 (76): làm while vì 76 > 72
                        answer[5] = 6 - 5 = 1
                        pop st -> [2]
                        tiếp tục: 76 > 75
                        answer[2] = 6 - 2 = 4
                        pop st -> []
                        st.push(6); st = [6]
                        answer = [1,1,4,2,1,1,0,0]

            i = 7 (73): while bỏ qua vì 73 < 76
                        st.push(7); st = [6,7]
                        answer = [1,1,4,2,1,1,0,0]

             Output sẽ là:  [1,1,4,2,1,1,0,0]
            */
        }
        return answer;
    }
};