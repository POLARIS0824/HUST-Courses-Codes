// https://www.luogu.com.cn/problem/P5691 方程的解数
// 折半搜索 meet in the middle

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
int k[10], p[10];
map<ll, int> sums; // 记录和的出现次数
ll ans = 0;

// 快速幂
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

// 枚举前半边未知数 x[start] ~ x[mid]
void dfs1(int pos, int end, ll sum) {
    if (pos > end) {
        sums[sum]++;
        return;
    }

    for (int x = 1; x <= m; ++x) {
        ll temp = (ll)k[pos] * power(x, p[pos]);
        dfs1(pos + 1, end, sum + temp);
    }
}

// 后半边
void dfs2(int pos, int end, ll sum) {
    if (pos > end) {
        if (sums.count(-sum)) {
            ans += sums[-sum];
        }
        return;
    }

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
    int mid = n / 2;
    dfs1(1, mid, 0);
    dfs2(mid + 1, n, 0);
    cout << ans << endl;
    return 0;
}