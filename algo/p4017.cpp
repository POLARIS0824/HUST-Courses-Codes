// https://www.luogu.com.cn/problem/P4017 最大食物链计数

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n species & m relations
    cin >> n >> m;

    vector<vector<int>> A(n + 1); // 吃 i 的生物
    vector<int> in(n + 1, 0); // 吃
    vector<int> out(n + 1, 0); // 被吃

    for (int i = 0; i < m; i++) {
        int a, b; // a 被 b 吃
        cin >> a >> b;
        A[a].push_back(b); // a -> b
        in[b]++;
        out[a]++;
    }
    // dp[i] 生产者到 i 的路径
    vector<long long> dp(n + 1, 0);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        // 生产者
        if (in[i] == 0) {
            q.push(i);
            dp[i] = 1;
        }
    }

    while (!q.empty()) {
        int k = q.front();
        q.pop();

        for (int v : A[k]) {
            dp[v] = (dp[v] + dp[k]) % 80112002;
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    long long res = 0;
    for (int i = 1; i <= n; i++) {
        // 消费者
        if (out[i] == 0) {
            res = (res + dp[i]) % 80112002;
        }
    }

    cout << res << endl;
    return 0;
}