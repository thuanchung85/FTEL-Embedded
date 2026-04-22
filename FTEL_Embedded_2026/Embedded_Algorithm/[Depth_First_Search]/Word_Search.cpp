#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /*
        cho matrix board = [["A","B","C","E"],
                            ["S","F","C","S"],
                            ["A","D","E","E"]]
        kiếm trong matrix đó có từ word = "ABCCED" hay không

        => kết quả là có. board = [["A","B","C"," "],
                                   [" "," ","C"," "],
                                   [" ","D","E"," "]]
    */

    //hàm kiểm tra từ  word = "ABCCED" có trong matrix hay không
    bool exist(vector<vector<char>>& board, string word)
    {
        int m = board.size();//số hàng matrix
        int n = board[0].size();//số cột matrix

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (Depth_First_Search(board, word, i, j, 0))
                {
                    return true;
                }
            }
        }
        return false;
    }

    //Giải Thuật Depth First Search, tìm 1 từ trong matrix, nếu có thì trả ra true
    bool Depth_First_Search(vector<vector<char>>& board, string& word, int i, int j, int index)
    {
        if (index == word.size()) return true; //dòng code này là chốt chặn để , đệ quy có thể stop khi chạy tới phần tử index cuối cùng của word, có nghĩa là đã lục tìm qua hết các từ trong word rồi.

        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) return false; // chốt chặn không cho input chỉ số i. và j đi quá khỏi index hàng và cột của matrix. nếu quá thì return false luôn.

        if (board[i][j] != word[index]) return false; // code chính làm nhiệm vụ so sánh một ký tự tại vị trí index trong chuổi word = "ABCCED", ví dụ "A" mà khác với ký tự board[i][j] trên matrix thì kết quả false luôn.

        //nếu board[i][j] có chưa ký tự mà tại đó == giống với word[index], ví dụ: ký tự "A" đầu tiên trong matrix , nó giống với ký tự "A" đầu tiên của  word = "ABCCED".
        //=> vậy nó được đánh dấu "#" vào ô đó gọi là ô đang check.
        char temp = board[i][j];// ta tạm thời save lại giá trị của ô matrix đang check đó, để kiểm tra 4 ô xung quanh xem sao, nếu 4 ô điều false hết thì coi như ô đó rớt đài => false
        //còn nếu  ô matrix đó, mà có 4 ô xung quanh nữa cũng ok thì ô đó chính thức là => true
        board[i][j] = '#'; // đánh dấu đã thăm, tránh việc 1 trong 4 ô xung quanh quy hồi lại chính ô này để check và nó lại thông báo ok, vậy là ta sẽ bị loop mãi với 1 cặp ô tham chiếu "yêu đương" qua lại

        // đi 4 hướng, lên, xuống, trái, phải, để định vị 4 ô xung quanh ô hiên tại và đệ quy chính 4 ô đó, để tìm thêm vùng lân cận tiếp. cứ thế lan rộng ra hết matrix.
        bool found = Depth_First_Search(board, word, i + 1, j, index + 1) ||
            Depth_First_Search(board, word, i - 1, j, index + 1) ||
            Depth_First_Search(board, word, i, j + 1, index + 1) ||
            Depth_First_Search(board, word, i, j - 1, index + 1);

        board[i][j] = temp; //Sau khi thử tất cả các hướng (i+1, i-1, j+1, j-1), ta cần khôi phục lại giá trị gốc (temp) để: Cho phép các nhánh DFS khác (xuất phát từ ô khác trong ma trận) vẫn có thể sử dụng ô này.
        //Đảm bảo ma trận không bị thay đổi vĩnh viễn, vì mỗi lần DFS chỉ là một thử nghiệm (backtracking).
        /*
            sau khi gọi DFS 4 hướng chính là để đảm bảo quy trình “đánh dấu rồi khôi phục” diễn ra đúng thứ tự:
            Đánh dấu: khi bước vào một ô, ta gán nó thành '#' để tránh quay lại chính ô này trong cùng một nhánh tìm kiếm.
            Khám phá: từ ô đó, ta thử đi sang 4 hướng khác nhau.
            Khôi phục: sau khi đã thử xong cả 4 hướng (dù thành công hay thất bại), ta khôi phục lại ký tự gốc (temp). Như vậy, khi quay lại từ một nhánh khác hoặc bắt đầu từ một ô khác, ô này vẫn còn nguyên giá trị ban đầu để được sử dụng lại. Nếu khôi phục trước khi DFS thì ô sẽ không còn bị đánh dấu, dẫn đến việc DFS có thể quay lại ngay lập tức → sai logic. Nếu không khôi phục sau DFS thì ma trận sẽ bị thay đổi vĩnh viễn, làm hỏng các lần tìm kiếm khác.
        */
        return found;
    }
};