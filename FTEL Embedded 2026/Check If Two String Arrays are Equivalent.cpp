#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // nối các chuỗi trong mảng lại rồi so sánh. nếu kết quả string giống nhau
    // thì là true, và ngược lại
    /*
        Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
        Output: true
        Explanation:
        word1 represents string "ab" + "c" -> "abc"
        word2 represents string "a" + "bc" -> "abc"
        The strings are the same, so return true.
    */

    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {

        int i = 0, j = 0; // index các phần tử string  trong vector<string> word1 ["ab", "c"] và word2 ["a", "bc"]
        int p = 0, q = 0; // index các ký tự trong string con vd: a, b -> "ab"

        //Vòng while chạy loop i va j ,cho đến khi một trong hai mảng hết.
        while (i < word1.size() && j < word2.size())
        {
            //Mỗi lần so sánh word1[i][p] với word2[j][q]
            if (word1[i][p] != word2[j][q])
                return false;

            // tăng con trỏ p của string con trong word1
            p++;

            //nếu con trỏ p chạy tới cuối chuổi string thì reset nó và tăng i để kiểm tra phần tử chuổi tiếp theo trong word1 
            if (p == word1[i].size()) {
                p = 0;
                i++;
            }

            // tăng con trỏ q của trinh con trong word2
            q++;

            //nếu con trỏ q chạy tới cuối chuổi string thì reset nó và tăng j để kiểm tra phần tử chuổi tiếp theo trong word2 
            if (q == word2[j].size()) {
                q = 0;
                j++;
            }
        }

        // nếu cả hai đều duyệt hết không fail khi chạy hết while  thì true.
        //nhưng phải check coi hai word1 và word2 có bằng size không nữa.
        return i == word1.size() && j == word2.size();
    }
};