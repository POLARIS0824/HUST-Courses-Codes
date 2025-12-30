// https://www.luogu.com.cn/problem/P1854 花店橱窗布置
// 核心思路：将f束花放入v个花瓶，每束花有不同的美学值，求最大美学值及方案
// 算法：动态规划 + 路径记录
// 状态定义：dp[i][j] 表示前i束花，第i束花放在第j个花瓶时的最大美学值
// 约束：每束花只能放一个花瓶，且后面的花必须放在后面的花瓶中
// 时间复杂度：O(f * v^2)

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
            cin >> a[i][j];  // a[i][j]: 第i束花放在第j个花瓶的美学值
        }
    }

    // dp[i][j]: 前i束花，第i束花放在第j个花瓶的最大美学值
    int MIN = -1e8;
    vector<vector<int>> dp(f + 1, vector<int>(v + 1, MIN));
    // pre[i][j]: 当花i放在瓶j时，花i-1放在哪个瓶子（用于路径回溯）
    vector<vector<int>> pre(f + 1, vector<int>(v + 1, 0));

    // 初始化：0束花的美学值为0
    for (int i = 0; i <= v; i++) {
        dp[0][i] = 0;
    }

    // 状态转移
    for (int i = 1; i <= f; i++) {
        // i束花，还剩 f-i 束花需要放置
        // 第j个瓶子，后面还剩 v-j 个瓶子
        // 约束：v-j >= f-i，即 j <= v-f+i
        for (int j = i; j <= v - f + i; j++) {
            // 枚举前一束花的位置k（必须在j之前）
            for (int k = i - 1; k < j; k++) {
                // 第i束花放在第j个瓶子，第i-1束花放在第k个瓶子
                int temp = dp[i - 1][k] + a[i][j];
                if (temp > dp[i][j]) {
                    dp[i][j] = temp;
                    pre[i][j] = k;  // 记录路径
                }
            }
        }
    }

    // 找到第f束花的最优位置
    int maxV = MIN;
    int last = -1;
    for (int j = f; j <= v; j++) {
        if (dp[f][j] > maxV) {
            maxV = dp[f][j];
            last = j;
        }
    }

    // 回溯路径
    vector<int> path(f + 1);
    int pos = last;
    for (int i = f; i >= 1; i--) {
        path[i] = pos;
        pos = pre[i][pos];
    }

    // 输出结果
    cout << maxV << endl;
    for (int i = 1; i <= f; i++) {
        cout << path[i];
        if (i < f) cout << " ";
    }
    cout << endl;
    return 0;
}