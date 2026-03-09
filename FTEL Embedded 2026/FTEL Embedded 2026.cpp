#include <iostream>
#include <vector>
#include "Merge Sorted Array.cpp"
using namespace std;

int main()
{
    cout << "Merge Sorted Array!\n";
    Solution obj;
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    obj.merge(nums1, 3, nums2, 3);

    for (int v : nums1) {
        cout << v << ' ';
        cout << '\n';
    }
}