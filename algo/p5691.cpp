// https://www.luogu.com.cn/problem/P5691 方程的解数
// 核心思路：求解多元方程 k1*x1^p1 + k2*x2^p2 + ... + kn*xn^pn = 0 的整数解数量
// 算法：折半搜索（Meet in the Middle）
// 策略：将n个变量分成两半，分别枚举前半部分和后半部分的所有可能值
// 优化：用哈希表存储前半部分的和，然后查找后半部分的负和是否存在
// 时间复杂度：O(m^(n/2))，相比暴力的O(m^n)大幅优化

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;              // n: 变量个数, m: 每个变量的取值范围[1, m]
int k[10], p[10];      // k[i]: 系数, p[i]: 指数
map<ll, int> sums;     // 存储前半部分所有可能的和及其出现次数
ll ans = 0;            // 答案：解的数量

// 快速幂：计算 base^exp
ll power(ll base, int exp) {
    if (exp == 0) {
        return 1;
    }
    ll half = power(base, exp / 2);
    if (exp % 2 == 0) {
        return half * half;
    } else {
        return half * half * base;
    }
}

// 枚举前半部分变量 x[start] ~ x[end]
// sum: 当前累加的和
void dfs1(int pos, int end, ll sum) {
    if (pos > end) {
        sums[sum]++;  // 记录这个和出现的次数
        return;
    }

    // 枚举当前变量的所有可能值
    for (int x = 1; x <= m; ++x) {
        ll temp = (ll)k[pos] * power(x, p[pos]);
        dfs1(pos + 1, end, sum + temp);
    }
}

// 枚举后半部分变量 x[start] ~ x[end]
void dfs2(int pos, int end, ll sum) {
    if (pos > end) {
        // 检查前半部分是否存在和为-sum的情况（使得总和为0）
        if (sums.count(-sum)) {
            ans += sums[-sum];
        }
        return;
    }

    // 枚举当前变量的所有可能值
    for (int x = 1; x <= m; ++x) {
        ll temp = (ll)k[pos] * power(x, p[pos]);
        dfs2(pos + 1, end, sum + temp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> k[i] >> p[i];
    }

    // 折半搜索：将变量分成两半
    int mid = n / 2;
    dfs1(1, mid, 0);      // 枚举前半部分 [1, mid]
    dfs2(mid + 1, n, 0);  // 枚举后半部分 [mid+1, n]

    cout << ans << endl;
    return 0;
}