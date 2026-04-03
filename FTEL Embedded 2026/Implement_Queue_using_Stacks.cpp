#include <stack>
using namespace std;

class MyQueue {
private:
    /*
    Ngăn xếp Stack là một cấu trúc dữ liệu tuyến tính hoạt động theo nguyên tắc LIFO (Last In First Out),
    nghĩa là các phần tử được đưa vào ngăn xếp cuối cùng sẽ là phần tử đầu tiên được lấy ra khỏi ngăn xếp.
    */
    stack<int> inStack;
    stack<int> outStack;

    // Hàm hỗ trợ: chuyển dữ liệu từ inStack sang outStack khi cần, move xong thì stack sẽ bi đảo ngược 
    void move() {
        //nếu outStack trống rổng thì mới chạy
        if (outStack.empty())
        {
            //nếu inStack có phần tử thì mới chạy
            while (!inStack.empty())
            {
                outStack.push(inStack.top());//hàm top() sẽ trả về phần tử nằm ở đỉnh của stack (phần tử được thêm vào cuối cùng).
                inStack.pop();
            }//outStack.push(inStack.top()); Vì stack là cấu trúc LIFO (Last In, First Out), nên khi chuyển toàn bộ phần tử từ inStack sang outStack, thứ tự sẽ bị đảo ngược.
        }
    }

public:
    MyQueue() {}

    //hàm add thêm một phần tử vào inStack
    void push(int x) {
        inStack.push(x);
    }

    //hàm lấy ra một phần tử đầu queue và xóa nó khỏi queue
    int pop() {
        move();//di chuyển hết các phần tử từ inStack qua outStack, outStack bị đảo ngược.
        int val = outStack.top();//hàm top() sẽ trả về phần tử nằm ở đỉnh của stack (phần tử được thêm vào cuối cùng).
        outStack.pop();//remove nó
        return val;//trả ra value của nó
    }

    //hàm lấy ra giá trị của phần tử đầu queue
    int peek() {
        move();
        return outStack.top();
    }

    //hàm kiểm tra queue có rổng hay không, bằng cách check inStack và outStack
    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */