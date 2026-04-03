
#include <vector>
using namespace std;

// Interface đã cho

    class CustomFunction {
    public:
        // Returns f(x, y) cho hai số nguyên dương x, y
       virtual  int f(int x, int y) = 0;
    };


/*

    Bạn có một hàm bí mật f(x, y) (giống như một công thức toán học nào đó, ví dụ có thể là x + y hoặc x * y).

    Bạn không biết công thức chính xác, chỉ biết rằng hàm này luôn tăng khi tăng x hoặc tăng y.

    Nghĩa là: nếu giữ nguyên y mà tăng x thì giá trị tăng.

    Nếu giữ nguyên x mà tăng y thì giá trị cũng tăng.

    Bạn được cho một số z. Nhiệm vụ là tìm tất cả các cặp số nguyên dương (x, y) sao cho f(x, y) == z.

    Ví dụ:

    Nếu công thức là f(x, y) = x + y và z = 5 thì ta cần tìm tất cả (x, y) sao cho x + y = 5. → Các cặp là (1,4), (2,3), (3,2), (4,1).

    Nếu công thức là f(x, y) = x * y và z = 5 thì ta cần tìm (x, y) sao cho x * y = 5. → Các cặp là (1,5), (5,1).

    ===========
    Trong đề, ta có 9 công thức bí mật khác nhau cho hàm f(x, y).

    Mỗi công thức được đánh số bằng function_id (từ 1 đến 9).

    Khi chạy chương trình, hệ thống sẽ đưa cho bạn hai thông tin:

    function_id: để biết đang dùng công thức nào (ví dụ: 1 là f(x,y) = x + y, 2 là f(x,y) = x * y, …).

    z: là giá trị mục tiêu mà bạn cần tìm các cặp (x, y) sao cho f(x, y) == z.

    Ví dụ cụ thể:

    Input: function_id = 1, z = 5
    Nghĩa là công thức đang dùng là f(x,y) = x + y.
    Bạn phải tìm tất cả (x,y) sao cho x + y = 5. → Kết quả: (1,4), (2,3), (3,2), (4,1).

    Input: function_id = 2, z = 5
    Nghĩa là công thức đang dùng là f(x,y) = x * y.
    Bạn phải tìm tất cả (x,y) sao cho x * y = 5. → Kết quả: (1,5), (5,1).

    Tóm lại: function_id chỉ định công thức nào đang được dùng. z là giá trị mục tiêu.
    Nhiệm vụ của bạn là tìm tất cả cặp (x,y) thỏa mãn công thức đó bằng đúng z.
*/

class Solution {
public:

    //do ta truyền vào hàm này 1 function nên là cần tạo interface "CustomFunction", để truyền vào hàm CustomFunction& customfunction.
    //hàm này trả ra một  array hai chiều, mà từng phần tử trong đó có dạng vector<int> do ta chỉ cần tìm cặp [x,y] cho nên => vector<vector<int>>, vd : [ [1,4],[2,3],[3,2],[4,1] ]
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z)
    {
        vector<vector<int>> res;// khởi tạo array hai chiều [[x,y]....[x,y]...]
        int x = 1, y = 1000;// hai con trỏ duyệt (two pointers) để tìm nghiệm, x chạy từ 1 -> 1000, còn y chạy ngược lại 1000 -> 1

        //tạo vòng while chạy cho x và y. x bắt đầu từ 1 và tăng dần lên đến 1000. y bắt đầu từ 1000 và giảm dần xuống đến 1.
        while (x <= 1000 && y >= 1)
        {
            int val = customfunction.f(x, y);//Ở mỗi bước lặp, ta gọi customfunction.f(x, y) để tính giá trị của hàm với cặp (x, y) hiện tại. lưu vào  biến val

            if (val == z)
            {
                res.push_back({ x, y });//Nếu giá trị val bằng z → lưu lại cặp (x, y) vào res. res = [[x,y]]
                x++;
                y--;
            }
            else if (val < z) //Nếu giá trị val nhỏ hơn z → ta phải tăng x (vì tăng x sẽ làm giá trị lớn hơn). ta không thể dùng y, vì y không thể tăng vì y là chạy theo chiều giảm dần
            {
                x++;
            }
            else  //Nếu giá trị val lớn hơn z → ta phải giảm y (vì giảm y sẽ làm giá trị nhỏ hơn). ta không thể dùng x vì x luôn tăng, dùng x cũng làm val tăng theo tiếp. nên chỉ có tác động vào y, giảm y.
            {
                y--;
            }
        }

        return res; //khi hêt while trả ra res = [[x,y]....[x,y]...]
    }
};