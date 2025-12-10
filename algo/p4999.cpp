// https://www.luogu.com.cn/problem/P4999 烦人的数学作业
// 数位 dp
// solve(R) - solve(L - 1)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

// dp[pos][sum]
ll dp[20][200];
int a[20];

// limit: 最高位限制
ll dfs(int pos, int sum, bool limit) {
    if (pos == -1) return sum;

    // 无限制 & 已算过
    if (!limit && dp[pos][sum] != -1) {
        return dp[pos][sum];
    }

    ll res = 0;
    // 枚举的最大数字取决于是否受限
    int high = limit ? a[pos] : 9;

    for (int i = 0; i <= high; ++i) {
        // limit: 当前受限 & 选了最大值
        res = (res + dfs(pos - 1, sum + i, limit && (i == high))) % MOD;
    }
    // 有限制的情况只有一次，不用记忆
    if (!limit) {
        dp[pos][sum] = res;
    }

    return res;
}

ll solve(ll x) {
    int pos = 0;
    while(x) {
        a[pos] = x % 10;
        x /= 10;
        pos++;
    }
    return dfs(pos - 1, 0, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    memset(dp, -1, sizeof(dp));

    while (t--) {
        ll l, r;
        cin >> l >> r;
        ll ans = (solve(r) - solve(l - 1)) % MOD;
        if (ans < 0) {
            ans += MOD;
        }
        cout << ans << endl;
    }
    return 0;
}