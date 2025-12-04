// https://www.luogu.com.cn/problem/P1854 花店橱窗布置

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int f, v; // 花束数 花瓶数
    cin >> f >> v;
    vector<vector<int>> a(f + 1, vector<int>(v + 1));
    for (int i = 1; i <= f; i++) {
        for (int j = 1; j <= v; j++) {
            cin >> a[i][j];
        }
    }

    // dp[i][j] 前i束花，第i束花放在第j个花瓶的最大美学值
    int MIN = -1e8;
    vector<vector<int>> dp(f + 1, vector<int>(v + 1, MIN));
    // pre[i][j] 当花i放在瓶j时，花i-1放在哪个瓶子
    vector<vector<int>> pre(f + 1, vector<int>(v + 1, 0));

    for (int i = 0; i <= v; i++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= f; i++) {
        // i flowers, f - i remains
        // v - j remains
        // v - j >= f - i
        // j <= v - f + i
        for (int j = i; j <= v- f + i; j++) {
            // flower i - 1 pos
            for (int k = i - 1; k < j; k++) {
                // i 放 j，i - 1 放 k
                int temp = dp[i - 1][k] + a[i][j];
                if (temp > dp[i][j]) {
                    dp[i][j] = temp;
                    pre[i][j] = k;
                }
            }
        }
    }
    int maxV = MIN;
    int last = -1;
    for (int j = f; j <= v; j++) {
        if (dp[f][j] > maxV) {
            maxV = dp[f][j];
            last = j;
        }
    }
    vector<int> path(f + 1);
    int pos = last;
    for (int i = f; i >= 1; i--) {
        path[i] = pos;
        pos = pre[i][pos];
    }
    cout << maxV << endl;
    for (int i = 1; i <= f; i++) {
        cout << path[i];
        if (i < f) cout << " ";
    }
    cout << endl;
    return 0;
}