#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    /* bài toán tìm ra một số và giá trị double của nó có cùng tồn tại trong array hay không?
    cho một array arr = [10,2,5,3], Ta đi kiếm hai cái chỉ số index của các phần tử trong array, tạm gọi là i và j:
    -> thỏa mãn  i >=0 và  j nhỏ hơn chiều dài của array, bắc buộc i phải khác j
    -> đồng thời phải thỏa được công thức array[i] = 2 * array[j]
    vì dụ căp: i = 0 tức là array[0] = 10 và j  = 2 tức là array[2] = 5 trong array.
    - 0 != 2
    - 0 >= 0, và 2 <= array.length = 4
    - i = 0 tức là array[0] = 10 và j  = 2 tức là array[2] = 5 trong array. 10 = 2 * 5

    -> true



    Ý tưởng đơn giản là dùng một unordered_set để lưu các phần tử đã duyệt, sau đó kiểm tra xem với mỗi phần tử x thì có tồn tại 2*x hoặc x/2 trong tập hay không.
    Điều này đảm bảo ta tìm được cặp thỏa mãn điều kiện.
    */
    bool checkIfExist(vector<int>& arr)
    {
        //seen là một unordered_set<int> chứa các phần tử đã duyệt qua trước đó. dùng để lưu trữ các phần tử duy nhất (không trùng lặp) nhưng không theo thứ tự.
        unordered_set<int> seen;

        /*
        Duyệt từng phần tử x trong mảng.
        Nếu trong tập seen đã có 2*x hoặc x/2 (khi x chia hết cho 2), thì trả về true.
        Nếu không, thêm x vào tập seen.
        Nếu duyệt hết mà không tìm thấy, trả về false.
        */
        for (int x : arr)
        {
            // kiểm tra xem đã có phần tử thỏa mãn chưa 1 trong hai option này: 
            //op 1 -> seen.count(y) sẽ trả về 1 nếu y có trong tập, ngược lại là 0.
            //op 2 -> (x % 2 == 0 && seen.count(x / 2))  Chỉ xét khi x là số chẵn (để đảm bảo x/2 là số nguyên) và trong seen có tồn tại giá trị (x/2).
            if (seen.count(2 * x) || (x % 2 == 0 && seen.count(x / 2)))
            {
                return true;// đã tìm thấy số x và có tồn tại giá trị double của nó trong array, trả ra true 
            }

            //thêm x vào tập seen. nếu x đó chưa bị dính tại if.
            seen.insert(x);
        }

        //chạy hết for mà không có vào true thì nghĩa là array không có thõa đề bài trả ra false
        return false;
    }
};