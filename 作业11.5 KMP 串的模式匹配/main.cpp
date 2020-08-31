#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
string::iterator KMP(string& str, string& pattern)
{
    vector<int> match(pattern.length(), -1);
    for (int rightEnd = 1; rightEnd < pattern.length(); rightEnd++) {
        auto curr = rightEnd - 1;
        while (curr != -1) {
            curr = match[curr];
            if (str[curr + 1] == str[rightEnd]) {
                match[rightEnd] = curr + 1;
                break;
            }
        }
    }
    /*
    for(auto i:match){
        cout << i << " ";
    }
    */
    auto i = 0;
    auto j = 0;
    while (i < str.length()) {
        if (str[i] == pattern[j]) {
            if (j == pattern.length() - 1) {
                return std::next(str.begin(), i - pattern.length() + 1);
            } else {
                i++;
                j++;
            }
        } else {
            if (j == 0) {
                i++;
            } else {
                j = match[j - 1] + 1;
            }
        }
    }
    return str.end();
}
int main()
{
    string str {};
    cin >> str;
    int numOfPatterns;
    cin >> numOfPatterns;
    std::stringstream ss {};
    for (int i = 0; i < numOfPatterns; i++) {
        string pattern {};
        cin >> pattern;
        //auto it = std::search(str.begin(), str.end(), pattern.begin(), pattern.end());
        /*
        int position = str.find(pattern);
        string::iterator it;
        if (position == std::string::npos) {
            it = str.end();
        } else {
            it = std::next(str.begin(), position);
        }
        */
        auto it = KMP(str, pattern);
        if (it == str.end()) {
            ss << "Not Found\n";
        } else {
            while (it != str.end()) {
                ss << *it;
                it++;
            }
            ss << "\n";
        }
    }
    cout << ss.str();
}