#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:

    // tìm số kẹo lớn nhất hiện tại trong các đứa trẻ, sau đó kiểm tra từng đứa trẻ, khi cộng thêm extraCandies vào thì nếu ai có số kẹo ít hơn  số kẹo của đứa có nhiều nhất thì đánh dấu false cho đứa đó.
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {

        // Tìm số kẹo lớn nhất hiện tại trong array candies
        int maxCandies = *max_element(candies.begin(), candies.end());
        cout << "Max candies hiện tại: " << maxCandies << endl;

        vector<bool> result;// khởi tạo array result 

        //duyệt hết array candies, kiểm tra từng phần tử 
        for (int i = 0; i < candies.size(); i++)
        {
            //lấy số kẹo hiện có của đứa trẻ đó cộng thêm với số kẹo extra coi nó là bao nhiêu 
            int newCandies = candies[i] + extraCandies;
            //cout << "Kid " << i + 1 << " có " << candies[i] << " kẹo, sau khi cộng thêm " << extraCandies << " = " << newCandies;

            //nếu số kẹo của nó sau khi được cho extra mà lớn hơn số kẹo hiện có của đứa trẻ có số kẹo max thì ok true 
            if (newCandies >= maxCandies)
            {
                //cout << " >= " << maxCandies << " -> true" << endl;
                result.push_back(true); //push_back trong C++ có nhiệm vụ thêm một phần tử mới vào cuối array
            }
            // ngược lại nếu đã cộng extra kẹo mà số kẹo vẫn nhỏ hơn số kẹo hiện có của đứa trẻ có số kẹo max thì false 
            else
            {
                //cout << " < " << maxCandies << " -> false" << endl;
                result.push_back(false);
            }
        }
        return result;
    }
};