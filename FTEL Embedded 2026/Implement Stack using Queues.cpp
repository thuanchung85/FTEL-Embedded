#include <queue>
using namespace std;
//tạo stack theo quy tắc last-in-first-out (LIFO) bằng cách dùng  hàng đợi (queue) 
class MyStack {
private:
    //tạo 2 queue q1 và q2
    //queue<int> là một hàng đợi (queue) chứa các phần tử kiểu int. Nó hoạt động theo nguyên tắc FIFO (First In, First Out) – nghĩa là phần tử nào được đưa vào trước thì sẽ được lấy ra trước.
    queue<int> q1, q2;

public:
    MyStack() {}

    //hàm push một phần tử mới vào stack theo quy tắc last-in-first-out (LIFO)
    //LIFO (Last In, First Out) là một phương pháp quản lý hàng tồn kho trong đó hàng hóa nhập kho sau cùng sẽ được xuất ra trước. 
    void push(int x)
    {
        // Thêm vào q2, sau đó chuyển toàn bộ phần tử từ q1 sang q2. Cuối cùng hoán đổi để q1 luôn chứa phần tử mới nhất ở đầu.
        // Đưa phần tử mới vào q2
        q2.push(x);

        // Chuyển toàn bộ phần tử từ q1 sang q2
        while (!q1.empty()) {
            q2.push(q1.front());//lấy từng phần tử của q1 nằm dưới đáy push vào q2 ,sau đó remove nó khỏi q1 
            q1.pop();
        }

        // sau khi q1 trống rổng thì ta chuyển hết phần tử của q2 vể lại q1 
        swap(q1, q2);
    }

    //hàm trả về phần tử đầu tiên và remove nó khỏi queue.
    int pop()
    {
        int val = q1.front();
        q1.pop();
        return val;
    }

    //hàm chỉ trả về giá trị của phần tử đầu tiên trong queue.
    int top()
    {
        return q1.front();
    }

    //hàm trả về true nếu queue empty.
    bool empty()
    {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */