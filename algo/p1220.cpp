// https://www.luogu.com.cn/problem/P1220 关路灯

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;
    vector<long long> pos(n + 1), power(n + 1); // 位置和功率
    vector<long long> prefix(n + 1, 0); // 前缀和

    for (int i = 1; i <= n; i++) {
        cin >> pos[i] >> power[i];
        prefix[i] = prefix[i - 1] + power[i];
    }
    long long total = prefix[n];
    long long MAX = 1e18;

    // dp[l][r][0] min at left
    // dp[l][r][1] min at right
    vector<vector<vector<long long>>> dp(n + 2,
        vector<vector<long long>>(n + 2, vector<long long>(2, MAX)));
    dp[c][c][0] = dp[c][c][1] = 0;
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            if (dp[l][r][0] >= MAX && dp[l][r][1] >= MAX) {
                continue;
            }
            long long remain = total - prefix[r] + prefix[l - 1];
            // left
            if (l > 1) {
                // l -> l - 1
                long long d1 = pos[l] - pos[l - 1];
                dp[l - 1][r][0] = min(dp[l - 1][r][0], dp[l][r][0] + d1 * remain);
                // r -> l - 1
                long long d2 = pos[r] - pos[l - 1];
                dp[l - 1][r][0] = min(dp[l - 1][r][0], dp[l][r][1] + d2 * remain);
            }

            // right
            if (r < n) {
                // r -> r + 1
                long long d1 = pos[r + 1] - pos[r];
                dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][1] + d1 * remain);
                // l -> r + 1
                long long d2 = pos[r + 1] - pos[l];
                dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][0] + d2 * remain);
            }
        }
    }
    // 人在 1 或 n
    cout << min(dp[1][n][0], dp[1][n][1]) << endl;
    return 0;
}