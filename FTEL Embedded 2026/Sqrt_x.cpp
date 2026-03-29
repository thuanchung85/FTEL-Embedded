class Solution {
public:
    //tính căn bậc hai và làm tròn, ví du: 4 lấy căn ra => 2, 8 lấy căn ra 2.82842 => làm tròn = 2
    /*
    Ban đầu ta biết chắc chắn căn bậc hai của 𝑥 phải nằm trong khoảng từ 1 đến x (trừ trường hợp đặc biệt x=0 hoặc 1).
     -> Thay vì thử từng số một, ta chọn số giữa để kiểm tra.

     -> Nếu bình phương của số giữa quá lớn so với 𝑥, ta biết căn bậc hai phải nằm bên trái (nhỏ hơn).

     -> Nếu bình phương của số giữa quá nhỏ so với 𝑥, ta biết căn bậc hai phải nằm bên phải (lớn hơn).

    Cứ thế, mỗi lần ta loại bỏ một nửa khoảng tìm kiếm.


    Ví dụ với 𝑥 = 8: ta cần tìm ra số nào mà bình phương lên bằng 8 trong khoản 1 -> 8, bao gồm 1,2,3,4,5,6,7,8

    Khoảng ban đầu: [1, 8].

    Lấy giữa: 1 và 8 là số 4 → 4 * 4 = 16 > 8
     → loại bỏ nửa bên phải, do dịch biến right  = 4 - 1,  nên còn các số từ 1, 2, 3.

    Lấy giữa: 1 và 3 là số 2 → 2 * 2 = 4 < 8
     → căn bậc hai phải lớn hơn, cập nhật ans=2, chỉ còn 3 đến 3 , do dịch biến left tới 1, left = 2 + 1.

    Lấy giữa: 3 → 3 * 3 = 9 > 8
     → loại bỏ nửa bên phải,tác động lên biến right = 3 -1,  còn [left = 3, right = 2] → dừng while.
    */
    int mySqrt(int x)
    {
        //nếu x = 0 hay x = 1, thì căn bậc hai cũng là x
        if (x == 0 || x == 1)
            return x; // Trường hợp nhỏ

        //nếu x là số dương khác , chạy while từ 1 đến x
        int left = 1, right = x, ans = 0;
        while (left <= right)
        {
            //Dùng biến long long cho mid * mid để tránh tràn số khi x lớn.
            long long mid = left + (right - left) / 2; // tránh tràn số, mid = (1 + 8) / 2 = 4

            //Nếu mid * mid == x thì trả về ngay.
            if (mid * mid == x)
            {
                return (int)mid;

            }
            //Nếu mid * mid < x thì dịch sang phải, đồng thời lưu mid vào ans.
            else if (mid * mid < x)
            {
                ans = (int)mid; // mid có thể là kết quả
                left = mid + 1;//đẩy left tới 1  theo chỉ số của mid
            }
            //Nếu mid * mid > x thì dịch sang trái.
            else
            {
                right = mid - 1;// lùi right về 1   theo chỉ số của mid
            }

            /*
            với x = 8
            Khởi tạo:
            left = 1, right = 8, ans = 0

            Vòng lặp 1:
            mid = 1 + (8 - 1) / 2 = 4
            mid * mid = 16 > 8 → dịch sang trái
            right = 3

            Vòng lặp 2:
            mid = 1 + (3 - 1) / 2 = 2
            mid * mid = 4 < 8 → lưu ans = 2, dịch sang phải
            left = 3

            Vòng lặp 3:
            mid = 3 + (3 - 3) / 2 = 3
            mid * mid = 9 > 8 → dịch sang trái
            right = 2

            Kết thúc:
            Vì left = 3 > right = 2, vòng lặp dừng.
            Trả về ans = 2.

            Kết quả: sqrt(8) làm tròn xuống là 2.
            */
        }

        //Kết quả cuối cùng là ans.
        return ans;
    }
};