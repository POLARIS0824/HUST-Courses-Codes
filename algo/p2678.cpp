// https://www.luogu.com.cn/problem/P2678 跳石头

#include <bits/stdc++.h>
using namespace std;

int l, n, m; // n 为岩石数
int rocks[60000];

bool isValid(int x);

int main() {
    cin >> l >> n >> m;
    rocks[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> rocks[i];
    }
    rocks[n + 1] = l;
    // 二分
    int low = 1;
    int high = l;
    int res = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isValid(mid)) {
            res = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << res << endl;
    return 0;
}

bool isValid(int x) {
    int remove = 0;
    int prev = 0; // 起点
    for (int i = 1; i <= n + 1; ++i) {
        if (rocks[i] - prev < x) {
            // remove
            if (++remove > m) {
                return false;
            }
        } else {
            prev = rocks[i];
        }
    }
    return true;
}