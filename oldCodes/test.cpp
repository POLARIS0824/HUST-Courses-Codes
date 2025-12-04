#include <bits/stdc++.h>
using namespace std;

bool isPal(string s);
bool op(string s, map<string, bool>& str); 

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
        } else {
            map<string, bool> str; 
            if (op(sub, str)) {
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

bool op(string s, map<string, bool>& str) {
    if (str.count(s)) {
        return str[s];
    }
    if (isPal(s)) {
        return str[s] = false; 
    }
    if (s.length() == 0) {
        return str[s] = false; 
    }
    string s1 = s.substr(1); 
    string s2 = s.substr(0, s.length() - 1); 
    if (isPal(s1) || isPal(s2)) {
        return str[s] = true; 
    }
    if (!op(s1, str) || !op(s2, str)) {
        return str[s] = true; 
    }
    return str[s] = false; 
}