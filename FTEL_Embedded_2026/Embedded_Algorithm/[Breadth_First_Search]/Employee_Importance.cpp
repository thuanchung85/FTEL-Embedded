#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

// Definition for Employee.
class Employee {
public:
    int id; //mã id
    int importance; //tầm quan trọng
    vector<int> subordinates; // các nhân viên trực thuộc cấp dưới
};


/*
    employees = [
        [1,5,[2,3]],
        [2,3,[]],
        [3,3,[]]
        ]

       -> Nhân viên id = 1, độ quan trọng (importance) = 5, có 2 cấp dưới trực tiếp là id = 2 và id = 3.

       -> Nhân viên id = 2, độ quan trọng = 3, không có cấp dưới.

       -> Nhân viên id = 3, độ quan trọng = 3, không có cấp dưới.

       nhập vào id = 1 thì sẽ return ra là 11. đó là tổng số độ quan trọng (importance) của cả 3 người (5 + 3 + 3) = 11
*/

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id)
    {
        // Đây là một hash map (bảng băm) ánh xạ từ khóa kiểu int sang giá trị kiểu Employee* (con trỏ đến đối tượng Employee).
        // nó giống như một "từ điển" mà mỗi id của nhân viên sẽ trỏ tới thông tin chi tiết của nhân viên đó.
        /*
            mp[1] = e1; // ánh xạ id=1 tới nhân viên e1
            mp[2] = e2; // ánh xạ id=2 tới nhân viên e2
            mp[3] = e3; // ánh xạ id=3 tới nhân viên e3
        */
        unordered_map<int, Employee*> mp;

        //duyệt qua từng phần tử trong vector employees. Mỗi phần tử là một con trỏ Employee*. nạp vào hash map mp[id] = e
        for (auto e : employees)
        {
            mp[e->id] = e;//Trong mỗi vòng lặp, ta lấy id của nhân viên đó (e->id) làm khóa trong unordered_map. Gán giá trị là chính con trỏ e (tức là toàn bộ thông tin nhân viên).
        }

        // Dùng Depth_First_Search lambda function trong C++:, đệ quy tìm ra tổng importance
        function<int(int)> Depth_First_Search = [&](int curId)
            {
                // Lấy nhân viên hiện tại từ id
                Employee* e = mp[curId];

                int total = e->importance; // lấy độ quan trọng của nhân viên đó, cho vào biến total trước

                for (int subId : e->subordinates) // Duyệt qua tất cả cấp dưới trực tiếp
                {
                    total += Depth_First_Search(subId);// đệ quy với chính nhân viên cấp dưới đó bằng chính hàm Depth_First_Search để lấy ra giá trị importance và cộng vào total
                }

                return total;//sau khi for chạy hết thì có nghĩa là đệ quy xong hết các nhân viên cấp dưới đã bị cộng dồn total , trả ra total
            };

        return Depth_First_Search(id);//gọi hàm  Depth_First_Search lambda function  chạy với id đã cho trong input.
    }
};