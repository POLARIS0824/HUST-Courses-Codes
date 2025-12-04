// https://www.luogu.com.cn/problem/P1106 删数问题

#include <bits/stdc++.h>
using namespace std;

int main() {
    string n;
    int k;
    if (!(cin >> n)) {
        return 0;
    }
    if (!(cin >> k)) {
        return 0;
    }

    string a;
    a.reserve(n.size());
    for (char i : n) {
        while (!a.empty() && k > 0 && a.back() > i) {
            // 还能删 && 栈顶更大
            a.pop_back(); 
            --k; 
        }
        a.push_back(i);
    }

    while (k > 0 && !a.empty()) {
        a.pop_back();
        --k;
    }

    // 去掉前导零
    size_t pos = a.find_first_not_of('0');
    if (pos == string::npos) {
        cout << 0; // 全是0
    } else {
        cout << a.substr(pos) << endl;
    }
    return 0;
}