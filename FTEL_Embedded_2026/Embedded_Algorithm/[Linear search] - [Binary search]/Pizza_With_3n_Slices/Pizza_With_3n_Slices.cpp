#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

class Solution {
public:
    /*
    -Bài này là chia pizza sao cho mình có lợi nhất.
    - Bạn Được chọn bất kỳ miếng nào, nhưng khi bạn chọn xong thì 2 người bạn sẽ lấy 2 miếng kế bên miếng bạn đã lấy.
    -Nguyên tắc lấy miếng pizza kế bên của người bạn A: là quay thuận chiều kim đồng hồ tính từ miếng bạn đã lấy, chạm vào miếng nào thì lấy miếng đó.
    -Nguyên tắc lấy miếng pizza kế bên của người bạn B: là quay ngược chiều kim đồng hồ tính từ miếng bạn đã lấy, chạm vào miếng nào thì lấy miếng đó.

    -> hãy tính toán sao cho kết quả cuối cùng khi chia xong Pizza thì bạn có số lượng các miếng công lại là lớn nhất

    ví dụ: pizza chia thành các miếng  slices = [8,9,8,6,1,1]
    - lần đầu chia pizza -> bạn lấy miếng số 8 . Suy ra => người A thuận chiều kim đồng hồ sẽ lấy miếng số 6. Và Người B ngược chiều kim đồng hồ sẽ lấy miếng số 9
    - lần 2 chia pizza -> bạn sẽ lấy miếng số 8. Suy ra => người A thuận chiều kim đồng hồ sẽ lấy miếng số 1. Và Người B ngược chiều kim đồng hồ sẽ lấy miếng số 1

    => cuối cùng bạn có 8 + 8 = 16 miếng pizza của bạn to nhất so với A là 7, và B là 10.
    */

    /*
        maxSum giải quyết bài toán tuyến tính (không còn vòng tròn nữa): Cho một đoạn con của mảng slices từ start đến end. Bạn cần chọn đúng n lát pizza trong đoạn này.

        Quy tắc: không được chọn hai lát kề nhau. Trả về tổng lớn nhất có thể.

    */
    int maxSum(vector<int>& slices, int start, int end, int n)
    {
        cout << "Trường Hợp: xet pizza từ miếng " << start << "--" << end << "\n";
        cout << "Cac giá trị các phan tu trong bánh pizza: ";

        for (int i = start; i <= end; i++) {
            cout << slices[i] << " ";
        }
        cout << "\n";

        int m = end - start + 1;//m: số lát pizza trong đoạn đang xét. tính từ start đến end . m = (4 - 0) + 1 = (5 - 1) + 1 = 5 (số phần tử trong đoạn con).
        cout << "So phan tu cua miếng bánh pizza = " << m << "\n";
        // tạo ra một ma trận 2 chiều (vector 2 chiều) để lưu trạng thái của bài toán DP
        // dp là một vector gồm m hàng. Mỗi hàng là một vector có n+1 cột. Tất cả các phần tử ban đầu đều bằng 0.
        vector<vector<int>> dp(m, vector<int>(n + 1, 0));
        //Giả sử m = 5, n = 2. Thì dp sẽ là một ma trận 5x3 (5 hàng, 3 cột):
        /*
            dp[0][0] = 0 , dp[0][1] = 0 , dp[0][2] = 0
            dp[1][0] = 0 , dp[1][1] = 0 , dp[1][2] = 0
            dp[2][0] = 0 , dp[2][1] = 0 , dp[2][2] = 0
            dp[3][0] = 0 , dp[3][1] = 0 , dp[3][2] = 0
            dp[4][0] = 0 , dp[4][1] = 0 , dp[4][2] = 0

            dp là tổng lớn nhất khi xét đến lát thứ i (tính từ start) và chọn đúng j lát.
        */


        dp[0][1] = slices[start]; // chọn lát pizza đầu tiên, nếu slices =[1,2,3,4,5] =>  dp[0][1] = 1.... nếu slices =[2,3,4,5,6] =>  dp[0][1] = 2. 
        cout << "=======DEBUG======" << "\n";
        cout << "DP lúc khởi đầu bóc lát pizza đầu tiên = " << dp[0][1] << "\n";
        cout << "-----" << "\n";
        for (int i = 1; i < m; i++) //for này chạy i = 1 -> 4, duyệt theo hàng của ma trận, tức là số lượng lát pizza đã xét đến (từ 1 đến m-1). m = 5 suy ra bạn đã xét đến lát pizza thứ 4, tức là đã xét hết đoạn con.
        {
            for (int j = 1; j <= n; j++) //for này chạy j = 1 -> 2, duyệt theo cột của ma trận, tức là số lượng lát pizza đã chọn (từ 1 đến n). n = 2 suy ra bạn đã chọn được 2 lát pizza.
            {

                int a = dp[i - 1][j]; // trường hợp a: không chọn lát pizza thứ i, thì tổng lớn nhất vẫn là dp[i-1][j], tức là tổng lớn nhất khi đã xét đến lát pizza thứ i-1 và vẫn chọn j lát pizza.

                int b = (i >= 2 ? dp[i - 2][j - 1] : 0) + slices[start + i]; // trường hợp b: chọn lát pizza thứ i, thì ta phải cộng giá trị của lát pizza thứ i (slices[start + i]) vào tổng lớn nhất khi đã xét đến lát pizza thứ i-2 và đã chọn j-1 lát pizza (dp[i-2][j-1]). Lý do là vì nếu chọn lát i thì không được chọn lát i-1 (vì kề nhau), nên ta phải xem xét tổng lớn nhất tại dp[i-2][j-1].

                dp[i][j] = max(a, b); // dp[i][j] sẽ là giá trị lớn nhất giữa hai trường hợp trên: không chọn lát i (a) hoặc chọn lát i (b).

                // In ra debug chi tiết
                cout << "Nếu ta bóc miếng pizza " << i << " có giá trị = " << slices[start + i] << ",  lần bóc " << j << " lát pizza "

                    << " | a=" << a
                    << " | b=" << b
                    << " | so max(" << a << "," << b << ") dp lúc này DP[" << i << "][" << j << "]=" << dp[i][j] << "\n";


            }
            cout << "-----" << "\n";
        }

        // In ra bảng DP để debug
        cout << "\nDP table (m=" << m << ", n=" << n << "):\n";
        cout << "bóc 0 lát  | " << "bóc 1 lát  | " << "bóc 2 lát \n";
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                cout << setw(4) << dp[i][j] << "         ";
            }
            cout << "\n";
        }
        cout << "Result = " << dp[m - 1][n] << "\n\n";


        /*
        phần tử dp[m-1][n] chính là ô nằm ở góc dưới bên phải của bảng. Nó mang ý nghĩa:
            i = m-1: đã xét hết toàn bộ lát pizza trong đoạn con (từ start đến end).
            j = n: đã chọn đúng n lát pizza.
            Giá trị ở ô này = tổng lớn nhất có thể đạt được với điều kiện trên.
        */
        return dp[m - 1][n];

    }

    //hàm trả ra số pizza to nhất ta có thể đạt được.
    int maxSizeSlices(vector<int>& slices)
    {
        int n = slices.size() / 3;// tìm ra số lần bóc pizza mà ta có thể có, vì array slices =[1,2,3,4,5,6] => size của slices = 6 => suy ra n = 6/3 = 2 => ta có 2 lần bóc pizza.

        /*
        Vấn đề của mảng vòng tròn chính là các miếng của bánh Pizza:
            Nếu mảng là tuyến tính (không vòng tròn), ta chỉ cần đảm bảo không chọn hai lát kề nhau.
            Nhưng vì pizza là vòng tròn, lát đầu tiên và lát cuối cùng cũng kề nhau.
            Nếu ta chọn cả lát đầu và lát cuối thì sẽ vi phạm quy tắc (vì chúng liền kề trên vòng tròn).

            ví dụ: nếu ta chạy code " maxSum(slices, 0, slices.size()-1, n) "
            tức là chạy từ phần tử 0 đến phần tử cuối của array slices = [1,2,3,4,5,6].
            => thì lúc đó có nguy cơ chọn cả lát đầu và lát cuối. Mà vì pizza là vòng tròn, hai lát này cũng kề nhau, nên sẽ vi phạm quy tắc “không chọn hai lát liền kề”.

            nên xuất hiện 2 trường hợp dưới
        */
        int case1 = maxSum(slices, 0, slices.size() - 2, n); // trường hợp 1: ta bỏ lát cuối slices =[1,2,3,4,5]

        int case2 = maxSum(slices, 1, slices.size() - 1, n); // trường hợp 2: bỏ lát đầu  slices =[2,3,4,5,6]

        return max(case1, case2);// trả ra case nào to nhất thì chọn.
    }
};