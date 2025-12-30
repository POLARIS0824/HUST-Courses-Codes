// https://www.luogu.com.cn/problem/P4999 烦人的数学作业
// 核心思路：计算区间[L, R]内所有数字的数位之和的总和
// 算法：数位DP（digit DP）
// 策略：solve(R) - solve(L-1)，将问题转化为求[0, x]范围内数位和的总和
// 状态定义：dp[pos][sum] 表示从第pos位开始，当前数位和为sum时的所有可能数位和的总和
// 时间复杂度：O(log x * sum_max)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

// dp[pos][sum]: 从第pos位开始，当前数位和为sum时的结果
ll dp[20][200];
int a[20];  // 存储数字的每一位

// limit: 是否受到原数字的限制（是否可以取到9）
// pos: 当前处理的位数（从高位到低位）
// sum: 当前数位和
ll dfs(int pos, int sum, bool limit) {
    // 递归边界：处理完所有位
    if (pos == -1) return sum;

    // 无限制且已经计算过，直接返回
    if (!limit && dp[pos][sum] != -1) {
        return dp[pos][sum];
    }

    ll res = 0;
    // 枚举当前位的数字（受限时最大为a[pos]，不受限时最大为9）
    int high = limit ? a[pos] : 9;

    for (int i = 0; i <= high; ++i) {
        // 递归处理下一位
        // 新的limit：当前受限 且 选了最大值
        res = (res + dfs(pos - 1, sum + i, limit && (i == high))) % MOD;
    }

    // 只有不受限的情况才记忆化（受限的情况只会出现一次）
    if (!limit) {
        dp[pos][sum] = res;
    }

    return res;
}

// 计算[0, x]范围内所有数字的数位和总和
ll solve(ll x) {
    int pos = 0;
    // 将x拆分成数位数组
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

    memset(dp, -1, sizeof(dp));  // 初始化为-1表示未计算

    while (t--) {
        ll l, r;
        cin >> l >> r;

        // 区间[L, R] = [0, R] - [0, L-1]
        ll ans = (solve(r) - solve(l - 1)) % MOD;
        if (ans < 0) {
            ans += MOD;  // 处理负数取模
        }
        cout << ans << endl;
    }
    return 0;
}