#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    //nhóm các chuổi con trong array mà có cùng các ký tự giống nhau, không tính vị trí các ký tự.
    /*
    vì dụ strs = ["eat","tea","tan","ate","nat","bat"]
    sẽ sắp xếp thành

    1 => ["bat"]
    2 => ["nat","tan"]
    3 => ["ate","eat","tea"]

    cuối cùng thành array = [["bat"],["nat","tan"],["ate","eat","tea"]]
    */

    //vector<string> strs = {"eat","tea","tan","ate","nat","bat"};là danh sách các chuỗi gốc thuộc cùng nhóm anagram.
    //suy ra vector<vector<string>> là array của array of string => array = [["bat"],["nat","tan"],["ate","eat","tea"]]

    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        /*
        tạo một hash map (bảng băm) với:
            Key: kiểu string
            Value: kiểu vector<string>
        */
        unordered_map<string, vector<string>> mp;


        //loop chạy hết array string strs = ["eat","tea","tan","ate","nat","bat"], kiểm tra từng chuổi con 
        for (string s : strs)
        {
            string key = s;
            sort(key.begin(), key.end()); // sắp xếp ký tự để tạo key, ví dụ "eat","tea","ate" => tất cả trở thành "aet"
            mp[key].push_back(s); // add KEY "aet" vào hash map mp VÀ VALUE của nó là lần lượt "eat","tea","ate"
            /*
            Sau vòng lặp, mp sẽ chứa:
                Key "aet" → Value ["eat","tea","ate"]
                Key "ant" → Value ["tan","nat"]
                Key "abt" → Value ["bat"]
            */
        }

        //là array của array of string result, Tạo một biến result là mảng 2 chiều (vector của vector). Mỗi phần tử trong result sẽ là một nhóm anagram.
        vector<vector<string>> result;
        //Duyệt qua từng phần tử trong unordered_map mp.
        for (auto& entry : mp)
        {
            result.push_back(entry.second);// chuyển hash map mp về thành lại vector<vector<string>> 
        }

        return result;
    }
};