class Solution {
public:
    /*Bài này chính kiểm tra xem số num nhập vào có phải là số chính phương hay không.

    Cách nhận biết số chính phương
        - Tính căn bậc hai: Nếu căn bậc hai của số là số nguyên, thì đó là số chính phương.
        - Chữ số tận cùng: Số chính phương chỉ có thể kết thúc bằng 0, 1, 4, 5, 6 hoặc 9.
        - Dạng số học: Số chính phương chỉ có thể có dạng 4n hoặc 4n+1
    */

    //Ta cần kiểm tra xem num có phải là số chính phương hay không. Dùng tìm kiếm nhị phân (Binary Search)
    /*
    Vì số chính phương là (𝑥 mủ 2), ta có thể tìm một số nguyên 𝑥 sao cho (𝑥 mủ 2) = 𝑛𝑢𝑚.

    Ta duyệt trong khoảng từ 1 đến num bằng tìm kiếm nhị phân để kiểm tra.

    Nếu tìm thấy (𝑚𝑖𝑑 mủ 2) = 𝑛𝑢𝑚 thì trả về true. Nếu không thì false.
    */
    bool isPerfectSquare(int num)
    {
        //check kiểm tra num bắt buộc phải từ 2 trở lên , nếu num = 1 thì trả true luôn.
        if (num < 2)
        {
            return true; // 1 là số chính phương
        }

        long long left = 2, right = num / 2;// tạo 2 biến, một chạy từ bên trái về phải nhỏ hơn số ở giữa, và một chạy từ bên phải về trái lớn hơn số ở giữa 

        //khi mà giá trị số của biến left và right còn chưa cắt nhau, hay nói cách khác là vượt qua nhau thì while còn chạy tiếp.
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            long long sq = mid * mid;

            if (sq == num)
                return true;
            else if (sq < num)
                left = mid + 1;
            else
                right = mid - 1;

            /* ví dụ số num = 16.
            => left = 2, right = 16/2 = 8

            Vòng 1: mid = 2 + (8 - 2)/2 = 5 → sq = 5 * 5 = 25 . suy ra 25 > 16 → chay else right = mid - 1 => 5 - 1 = 4 => thu hẹp right sang trái (right = 4).

            Vòng 2: mid = 2 + (4-2)/2 = 3 → sq = 3 * 3 = 9. suy ra 9 < 16 → chạy else if left = mid + 1 => 3 + 1 = 4 => dịch left sang phải (left = 4).

            Vòng 3: mid = 4 + (4 - 4)/2 = 4 → sq = 4 * 4 = 16. suy ra 16 == 16 → tìm thấy số chính phương.
            */
        }

        //nếu chạy hết while mà vẩn không ra số chính phương thì trả ra false.
        return false;
    }
};