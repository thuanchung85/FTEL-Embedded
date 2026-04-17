#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    /*
        trò chơi xếp ô gạch từ 1 đến 5 theo thứ tự từ trên xuống từ trái qua phải.
        ví dụ: board = [[1,2,3],
                        [4,0,5]]
                        -> di chuyển số 0 qua chổ số 5, là xong =>  board = [[1,2,3],
                                                                             [4,5,0]]

        ví dụ:  board = [[4,1,2],
                         [5,0,3]]
                         ->  di chuyển số 0 qua chổ số 5, là =>  board = [[4,1,2],
                                                                          [0,5,3]]

                         ->  di chuyển số 0 qua chổ số 4, là =>  board = [[0,1,2],
                                                                          [4,5,3]]

                         ->  di chuyển số 0 qua chổ số 1, là =>  board = [[1,0,2],
                                                                          [4,5,3]]

                         ->  di chuyển số 0 qua chổ số 2, là =>  board = [[1,2,0],
                                                                          [4,5,3]]

                         ->  di chuyển số 3 qua chổ số 0, là =>  board = [[1,2,3],
                                                                          [4,5,0]]
    */

    /*
    Cách hoạt động có thể hình dung như sau:

    Bước 1: Tìm vị trí hiện tại của số 0 trong chuỗi trạng thái.

    Bước 2: Dựa vào bảng neighbors, xác định các ô kề mà 0 có thể hoán đổi.

    Bước 3: Với mỗi ô kề, tạo một bản copy của trạng thái (new_state), rồi swap để sinh ra trạng thái mới.

    Bước 4: Nếu trạng thái mới chưa từng xuất hiện (visited), ta lưu lại và đưa vào hàng đợi BFS.

    Bước 5: BFS sẽ lần lượt lấy từng trạng thái trong queue ra, tiếp tục di chuyển 0 theo các hướng hợp lệ, cho đến khi gặp trạng thái đích "123450".

     Nói ngắn gọn: BFS giống như cho số 0 “chạy khắp bàn cờ” theo luật di chuyển, mỗi lần chạy sinh ra một trạng thái mới, và ta lưu lại tất cả các trạng thái đã đi qua để tránh lặp. Khi nào trạng thái mới trùng với trạng thái yêu cầu thì dừng lại, trả về số bước.
    */

    int slidingPuzzle(vector<vector<int>>& board)
    {
        {
            //bước 1: Biểu diễn trạng thái Chuyển ma trận 2x3 thành chuỗi (string) để dễ lưu trong tập hợp visited. Ví dụ: [[1,2,3],[4,0,5]] → "123405".
            //chuyển array board = [[1,2,3],[4,0,5]] => thành string, start = "123405"
            string start;
            for (auto& row : board)
            {
                for (int x : row)
                    start.push_back(x + '0');
            }

            //bước 2: Xác định trạng thái đích . "123450" (tương ứng với [[1,2,3],[4,5,0]]).
            string target = "123450"; // chuổi kết quả mà chúng ta muốn là "123450"

            //bước 3: Xác định các bước di chuyển hợp lệ của số 0. 
            //Với mỗi vị trí của số 0, ta cần biết nó có thể hoán đổi với những ô nào.
            //Ta đánh số vị trí từ 0 → 5 theo thứ tự trái sang phải, trên xuống dưới:
            vector<vector<int>> neighbors =
            {
                //ví dụ matrix ta hình dung nó theo index thế này
                /*
                    board = [[1,2,3],
                             [4,0,5]]
                    => nhìn dưới con mắt index thì nó ra sau

                    board = [[ số 1 (vị trí là 0), số 2 (vị trí là 1), số 3 (vị trí là 2)],
                             [ số 4 (vị trí là 3), số 0 (vị trí là 4), số 5 (vị trí là 5)]]
                */
                {1, 3},    // khi ta ở vị trí 0 ta có thể hoán đổi với 2 vị trí đó là vị trí 1, và vị trí 3.
                {0, 2, 4}, // khi ta ở vị trí 1 ta có thể hoán đổi với 3 vị trí đó là vị trí 0, và vị trí 2, và vị trí 4.

                {1, 5},    // khi ta ở vị trí 2 ta có thể hoán đổi với 2 vị trí đó là vị trí 1, và vị trí 5.
                {0, 4},    // khi ta ở vị trí 3 ta có thể hoán đổi với 2 vị trí đó là vị trí 0, và vị trí 4.

                {1, 3, 5}, // khi ta ở vị trí 4 ta có thể hoán đổi với 3 vị trí đó là vị trí 1, và vị trí 3, và vị trí 5.
                {2, 4}     // khi ta ở vị trí 5 ta có thể hoán đổi với 2 vị trí đó là vị trí 2, và vị trí 4.
            };


            //bước 4: Thuật toán BFS
            //Bắt đầu từ trạng thái ban đầu, đưa vào queue.
            //Mỗi bước: lấy trạng thái hiện tại, tìm vị trí 0, sinh ra các trạng thái mới bằng cách swap với ô kề.
                //Nếu gặp trạng thái đích, trùng chuổi kết quả mà chúng ta muốn là "123450" → trả về số bước enend game.
                //Nếu duyệt hết mà không gặp → trả về -1.
            queue<pair<string, int>> q;
            unordered_set<string> visited;
            q.push({ start, 0 });
            visited.insert(start);

            while (!q.empty())
            {
                //lấy từ queue ra phần tử đầu tiên cần xữ lý, và remove nó
                pair<string, int> front = q.front(); // lấy phần tử đầu tiên trong queue
                string state = front.first;         // trạng thái hiện tại ví dụ state = "123405"
                int steps = front.second;           // số bước đã đi ví dụ steps = 0
                q.pop();//remove khỏi queue


                //điều kiện end game win state == target == "123450"
                if (state == target)
                    return steps;// trả ra số bước đã dùng.

                //giải thuật BFS
                int zero_pos = state.find('0');//lúc này là lúc tìm ra vị trí số 0 đang ở ô nào. Và lục trong array neighbors coi coi các vị trí các ô xung quanh mà 0 có thể tương tác với nó
                // ví dụ nếu zero_pos = 4 => suy ra neighbors[zero_pos] sẽ là các ô neighbors[4] =  {1, 3, 5}, rồi ta for xét 3 phần tử đó để xữ lý.
                for (int nei : neighbors[zero_pos])    //duyệt for cho ví dụ: neighbors[4] =  {1, 3, 5} => nei là 1, 3, 5 chạy 3 vòng.
                {
                    string new_state = state;//state là chuỗi biểu diễn bàn cờ hiện tại (ví dụ "123405"). new_state lúc này sẽ có giá trị giống hệt state ngay khi khởi tạo.
                    swap(new_state[zero_pos], new_state[nei]); //Sau đó ta dùng swap(new_state[zero_pos], new_state[nei]); để tạo ra một trạng thái mới bằng cách hoán đổi vị trí của 0 với một ô kề.
                    /*
                    state = "123405"
                    zero_pos = 4 (ô trống ở index 4) => neighbors[4] =  {1, 3, 5} => ta có thể swap với ô vị trí 1, sau đó ô vị trí 3, sau đó ô vị trí 5
                    => làm swap với ô vị trí 1 trước. vậy   swap(new_state[4], new_state[1]); => new_state = "103425"

                    Kết quả:  new_state = "103425"
                    */

                    //check nếu new_state = "103425" chưa có trong visited unordered_set<string>, visited dùng để lưu tất cả các trạng thái đã duyệt qua
                    if (!visited.count(new_state)) //visited.count(new_state) sẽ trả về số lần xuất hiện của new_state trong tập hợp. if (!visited.count(new_state)) nghĩa là: chỉ xử lý tiếp nếu trạng thái mới chưa từng xuất hiện.
                    {
                        visited.insert(new_state);// nếu chưa có trong tập hợp visited thì add nó vào visited
                        q.push({ new_state, steps + 1 });//  ta push thêm 1 object cặp gồm chuổi new_state = "103425" và  steps + 1 => suy ra ta có  {"103425",1} add vào queue để BFS chạy tiếp
                    }
                }

            }
            return -1;
        }
    }
};