/*
Queue thường (size = 5):

Thêm: [1, 2, 3, 4, 5] → đầy.
Xóa 2 phần tử: [_, _, 3, 4, 5].
Muốn thêm nữa? Không được, vì rear đã ở cuối mảng → lãng phí 2 ô trống.


Circular Queue (size = 5):

Thêm: [1, 2, 3, 4, 5] → đầy.
Xóa 2 phần tử: [_, _, 3, 4, 5].
Thêm tiếp: [6, 7, 3, 4, 5] → tận dụng lại 2 ô trống phía trước.
*/

class MyCircularQueue {
private:
    int* queue;
    int front;
    int rear;
    int size;
    int count;

public:
    // constructor Khởi tạo queue với kích thước k
    MyCircularQueue(int k)
    {
        size = k;
        queue = new int[k]; //Mảng queue có độ dài là k : lưu các phần tử kiểu int.

        front = 0;//Biến front: sẽ giữ chỉ số index phần tử đầu tiên.
        rear = 0;//Biến rear: sẽ giữ chỉ số index ngay sau phần tử cuối cùng (giúp dễ phân biệt full/empty).
        count = 0;//Biến count: số phần tử hiện có trong queue (hoặc ta có thể dùng công thức (rear - front + size) % size).
    }

    //hàm add một phần tử vào queue
    bool enQueue(int value)
    {

        //chặn add nếu queue đã full
        if (isFull()) return false;

        //nếu queue pass check full thì ok, add vào queue tại index rear
        queue[rear] = value;
        /*
        Bạn có thể truy cập bất kỳ phần tử nào bằng chỉ số (queue[i]), giống như mảng bình thường.
        Nhưng về mặt nguyên tắc sử dụng Queue, ta chỉ nên thao tác qua các hàm enQueue (thêm cuối) và deQueue (xóa đầu) để đảm bảo đúng quy tắc FIFO.
        Nếu bạn tự ý gán queue[index] = value;, thì sẽ phá vỡ cấu trúc FIFO, vì bạn đang bỏ qua cơ chế quản lý front và rear.
        */

        //Ta cần dòng lệnh rear = (rear + 1) % size; để đảm bảo chỉ số rear luôn nằm trong phạm vi hợp lệ của mảng và tạo hiệu ứng “vòng tròn” cho queue.
        /*
        Giải thích chi tiết
        Trong mảng bình thường, nếu ta cứ tăng rear++, đến lúc rear == size thì sẽ vượt quá giới hạn mảng (out of bound).
        Với circular queue, khi rear chạm cuối mảng (size - 1), ta muốn nó quay lại vị trí đầu (0) để tận dụng không gian trống phía trước.
        Phép toán modulo % size chính là cách để “quay vòng”:
        Ví dụ: rear = 2, size = 3 → (rear + 1) % size = (2 + 1) % 3 = 0.
        Nghĩa là sau khi thêm phần tử ở cuối, chỉ số rear quay về đầu mảng.

        rear = (rear + 1) % size; giúp rear luôn nằm trong phạm vi [0, size-1] và tạo cơ chế vòng tròn để tận dụng không gian trống phía trước khi dequeue.

        Minh họa vòng quay
        Giả sử queue có kích thước 2 (chỉ số hợp lệ là 0 và 1):

        Ban đầu rear = 0 → thêm phần tử vào vị trí 0.

        Sau đó rear = (0+1)%2 = 1 → thêm phần tử vào vị trí 1. Khi ta làm 1 % 2 = 1 (vì 1 chia 2 không được, nó sẽ ra là 0 cho nên ta còn dư  1)

        Nếu tiếp tục thêm nữa: rear = (1+1)%2 = 0 → quay lại vị trí đầu.

        Nhờ vậy, chỉ số rear luôn nằm trong phạm vi [0, size-1] và khi đến cuối mảng thì quay vòng lại đầu, đúng với cơ chế circular queue.
        */
        rear = (rear + 1) % size;// tăng rear index

        count++;//khi add một phần tử vào queue thì count tăng 1.
        return true;
    }

    //hàm xóa một phần tử khỏi queue
    bool deQueue()
    {
        //chặn nếu queue đã empty thi khỏi chạy.
        if (isEmpty()) return false;

        //dịch index front về sau 1 bậc, để xóa phần tử đầu queue, theo quy tắc FIFO,  FIFO (First In, First Out) order
        front = (front + 1) % size;
        count--;//giảm count đi 1.
        return true;
    }

    //hàm trả ra phần tử đứng đầu queue
    int Front() {
        //nếu queue empty thì trả ra -1
        if (isEmpty()) return -1;

        //nếu ok thì trả ra phần tử đang đứng đầu queue
        return queue[front];
    }

    //hàm trả ra phần tử cuối queue
    int Rear() {
        //nếu queue rổng thì trả ra -1
        if (isEmpty()) return -1;

        //nếu ok thì trả ra phần tử cuối queue
        return queue[(rear - 1 + size) % size];
    }

    //hàm kiểm tra queue rổng.
    bool isEmpty() {
        return count == 0;
    }

    //hàm trả ra Queue đã đầy hay chưa
    bool isFull() {
        return count == size;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */