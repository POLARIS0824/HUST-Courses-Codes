// https://www.luogu.com.cn/problem/P4017 最大食物链计数
// 核心思路：计算从生产者到消费者的所有食物链数量
// 算法：拓扑排序 + 动态规划
// 状态定义：dp[i] 表示从生产者到节点i的路径数量
// 关键：生产者（入度为0）到消费者（出度为0）的路径计数
// 时间复杂度：O(n + m)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n: 物种数, m: 捕食关系数
    cin >> n >> m;

    vector<vector<int>> A(n + 1); // A[i]: 吃i的生物列表
    vector<int> in(n + 1, 0);     // 入度：被吃的次数
    vector<int> out(n + 1, 0);    // 出度：吃其他生物的次数

    for (int i = 0; i < m; i++) {
        int a, b; // a 被 b 吃
        cin >> a >> b;
        A[a].push_back(b); // a -> b（食物链方向：从被吃者指向捕食者）
        in[b]++;   // b 的入度增加
        out[a]++;  // a 的出度增加
    }

    // dp[i]: 从生产者到节点i的路径数量
    vector<long long> dp(n + 1, 0);
    queue<int> q;

    // 初始化：找出所有生产者（入度为0，不被任何生物吃）
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
            dp[i] = 1;  // 从生产者到自己只有1条路径
        }
    }

    // 拓扑排序 + DP
    while (!q.empty()) {
        int k = q.front();
        q.pop();

        // 遍历所有吃k的生物
        for (int v : A[k]) {
            dp[v] = (dp[v] + dp[k]) % 80112002;  // 路径数累加
            in[v]--;
            if (in[v] == 0) {  // 所有前置节点都处理完
                q.push(v);
            }
        }
    }

    // 统计所有消费者（出度为0，不吃任何生物）的路径数
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        if (out[i] == 0) {  // 消费者
            res = (res + dp[i]) % 80112002;
        }
    }

    cout << res << endl;
    return 0;
}