// https://www.luogu.com.cn/problem/P1658 购物

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n;
    cin >> x >> n;
    vector<int> value(n);
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    sort(value.begin(), value.end());
    if (value[0] != 1) {
        cout << -1 << endl;
        return 0;
    }

    int ok = 0; // 已经凑到 ok
    int res = 0;

    while (ok < x) {
        int coin = 0;
        for (int v : value) {
            if (v <= ok + 1) { // 该凑 ok + 1
                coin = v;
            } else {
                break;
            }
        }
        if (coin == 0) {
            cout << -1 << endl;
            return 0;
        }
        ok += coin;
        res++;
    }

    cout << res << endl;
    return 0;
}