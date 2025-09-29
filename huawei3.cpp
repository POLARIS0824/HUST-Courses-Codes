#include <bits/stdc++.h>
using namespace std;

bool isPal(string s);
bool op(string s, int n);

int main() {
    string s;
    getline(cin, s);
    int q;
    cin >> q;
    vector<vector<int>> query(q, vector<int>(2));
    for (int i = 0; i < q; i++) {
        cin >> query[i][0] >> query[i][1];
    }
    for (int i = 0; i < q; i++) {
        int l = query[i][0], r = query[i][1];
        string sub = s.substr(l - 1, r - l + 1);
        if (isPal(sub)) {
            cout << "TSUH" << endl;
        }
        else {
            if (op(sub, 0)) {
                cout << "TSUH" << endl;
            }
            else {
                cout << "HUST" << endl;
            }
        }
    }
}

bool isPal(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

bool op(string s, int n) {
    if (isPal(s)) {
        if (n % 2 == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        string s1 = s.substr(1);
        string s2 = s.substr(0, s.size() - 1);
        bool res1 = op(s1, n + 1);
        bool res2 = op(s2, n + 1);
        if (res1 && res2) {
            return true;
        }
    } 
}



// bool op(string s) {
//     int n = s.length();
//     if (n == 0) return false;
//     vector<vector<bool>> dp(n, vector<bool>(n, false));
//     for (int i = 0; i < n; i++) {
//         dp[i][i] = false;
//     }
//     for (int len = 2; len <= n; len++) {
//         for (int i = 0; i <= n - len; i++) {
//             int j = i + len - 1;
//             bool res1 = (isPal(s.substr(i + 1, len - 1)));
//             bool res2 = (isPal(s.substr(i, len - 1)));
//             if (res1 && res2) {
//                 dp[i][j] = false; 
//             } else if (!res1 && !res2) {
//                 dp[i][j] = dp[i+1][j-1];  
//             } else {
//                 dp[i][j] = true;  
//             }
//         }
//     }
//     return dp[0][n-1];
// }