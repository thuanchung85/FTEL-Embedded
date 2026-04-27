#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    /*
        cho array  rooms = [[1],[2],[3],[]]. có nghĩa là
            căn phòng rooms[0] = [1] => căn phòng có index = 0 có chứa key mở khóa căn phòng có index = 1
            căn phòng rooms[1] = [2] => căn phòng có index = 1 có chứa key mở khóa căn phòng có index = 2
            căn phòng rooms[2] = [3] => căn phòng có index = 2 có chứa key mở khóa căn phòng có index = 3
            căn phòng rooms[3] = [] => căn phòng có index = 3 không có chứa key
            => vậy ta có thể mở khóa tất cả các phòng , return true

        cho array rooms = [[1,3],[3,0,1],[2],[0]]. có nghĩa là
            căn phòng rooms[0] = [1,3] => căn phòng có index = 0 có chứa key mở khóa căn phòng có index = 1 và index = 3
            căn phòng rooms[1] = [3,0,1] => căn phòng có index = 1 có chứa key mở khóa căn phòng có index = 3 , index = 0 và index = 1
            căn phòng rooms[2] = [2] => căn phòng có index = 2 có chứa key mở khóa căn phòng có index = 2
            căn phòng rooms[3] = [0] => căn phòng có index = 3 có chứa key mở khóa căn phòng có index = 0
            => vậy ta có căn phòng có index = 2 là không có chìa khóa bên ngoài để mở nó, return false
    */
    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        int soLuongPhong = rooms.size();//số lượng các căn phòng có trong array  rooms = [[1],[2],[3],[]], soLuongPhong = 4

        vector<bool> visited(soLuongPhong, false);// một array ghi lại phòng nào đã tới thì true, chưa tới thì false visited= {false, false, false, false}

        queue<int> q;//một queue để xử lý các căn phòng lần lượt.

        visited[0] = true;//xữ lý căn phòng có index = 0 trước
        q.push(0);//đưa index của căn phòng số 0 vào queue để bắt đầu chạy while xữ lý.

        while (!q.empty()) //nếu queue vẫn còn có phòng cần check thì còn chạy mãi
        {
            int room = q.front();//đem căn phòng đầu tiên có trong queue ra xữ lý, lúc này chính là room có index = 0
            q.pop();//remove nó khỏi queue

            for (int key : rooms[room]) //lục tìm, và check các chìa khóa có trong căn phòng đó, bằng dòng for
            {
                if (!visited[key]) // kiểm tra xem phòng có index = key đã được thăm chưa. Nếu visited[key] == false nghĩa là phòng đó chưa được mở/duyệt.
                {
                    visited[key] = true;// chuyển nó thành true, coi như check phòng visited[key] là mở được.
                    q.push(key);// đem index của phòng visited[key] đó vào queue, nghĩa là ta sẽ đem phòng mới mở được đi vào queue để check tiếp từ nó. while chạy tiếp từ căn phòng đó.
                }
            }
        }

        // Kiểm tra tất cả phòng đã được thăm visited = {true, true, true ,true}, thì ok, còn nếu có 1 phần tử false thì trả ra false luôn.
        for (bool v : visited) {
            if (!v)
                return false;
        }
        return true;
    }
};