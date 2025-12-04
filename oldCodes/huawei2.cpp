#include <bits/stdc++.h>
using namespace std;    

string hex(vector<int> digits);

int main(){
    string s;
    getline(cin, s);
    int n = s.size();
    bool flag = false;
    vector<int> digits;
    string result = "";
    int i = 0;
    while (i < n) {
        if (i + 1 < n && s[i] == '{' && s[i+1] != '}') {
            int j = i + 1;
            vector<int> cur;
            while (j < n && s[j] != '}') {
                if (isdigit(s[j])) {
                    cur.push_back(s[j] - '0');
                }
                j++;
            }
            string hex = ::hex(cur);
            result += hex;
            i = j + 1;
        } else {
            result += s[i];
            i++;
        }
    }
    cout << result << endl;
}

string hex(vector<int> digits) {
    int res = 0;
    for (int i = 0; i < digits.size(); i++) {
        res += digits[i] * pow(10, digits.size() - i - 1);
    }
    string hex = "0123456789ABCDEF";
    string ans = "";
    while (res) {
        ans = hex[res % 16] + ans;
        res /= 16;
    }
    return "0x" + ans;
}