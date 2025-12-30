// https://www.luogu.com.cn/problem/P1220 关路灯
// 核心思路：从起始位置出发，选择最优的路径顺序关闭所有路灯，最小化总功耗
// 算法：区间 DP
// 状态定义：dp[l][r][0/1] 表示关掉 [l, r] 区间内的灯后，人在左端点l(0)或右端点r(1)时的最小功耗
// 状态转移：从区间 [l, r] 向两侧扩展到 [l-1, r] 或 [l, r+1]
// 时间复杂度：O(n^2)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;
    vector<long long> pos(n + 1), power(n + 1); // 位置和功率
    vector<long long> prefix(n + 1, 0);         // 功率前缀和

    for (int i = 1; i <= n; i++) {
        cin >> pos[i] >> power[i];
        prefix[i] = prefix[i - 1] + power[i];
    }

    long long total = prefix[n];  // 总功率
    long long MAX = 1e18;         // 表示不可达状态

    // dp[l][r][0] 表示关掉 [l, r] 区间的灯，人在左端点 l 的最小功耗
    // dp[l][r][1] 表示关掉 [l, r] 区间的灯，人在右端点 r 的最小功耗
    vector<vector<vector<long long>>> dp(n + 2,
        vector<vector<long long>>(n + 2, vector<long long>(2, MAX)));

    dp[c][c][0] = dp[c][c][1] = 0;  // 初始状态：在起始位置，功耗为 0

    // 按区间长度枚举
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            if (dp[l][r][0] >= MAX && dp[l][r][1] >= MAX) {
                continue;  // 当前状态不可达，跳过
            }

            // remain: [l, r] 区间外的灯还在亮着的总功率
            long long remain = total - prefix[r] + prefix[l - 1];

            // 向左扩展：从 [l, r] 到 [l-1, r]
            if (l > 1) {
                // 从左端点 l 移动到 l-1
                long long d1 = pos[l] - pos[l - 1];
                dp[l - 1][r][0] = min(dp[l - 1][r][0], dp[l][r][0] + d1 * remain);

                // 从右端点 r 移动到 l-1
                long long d2 = pos[r] - pos[l - 1];
                dp[l - 1][r][0] = min(dp[l - 1][r][0], dp[l][r][1] + d2 * remain);
            }

            // 向右扩展：从 [l, r] 到 [l, r+1]
            if (r < n) {
                // 从右端点 r 移动到 r+1
                long long d1 = pos[r + 1] - pos[r];
                dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][1] + d1 * remain);

                // 从左端点 l 移动到 r+1
                long long d2 = pos[r + 1] - pos[l];
                dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][0] + d2 * remain);
            }
        }
    }

    // 答案：关掉所有灯 [1, n]，人在左端点 1 或右端点 n 时的最小功耗
    cout << min(dp[1][n][0], dp[1][n][1]) << endl;
    return 0;
}