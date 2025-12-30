// https://www.luogu.com.cn/problem/P1658 购物
// 核心思路：用有限的硬币面值组合出目标金额，求最少硬币数
// 算法：贪心 + 连续区间覆盖
// 策略：维护已经能凑出的最大值ok，每次选择不超过ok+1的最大硬币，扩展可达范围
// 关键：如果存在面值1的硬币，可以保证连续性
// 时间复杂度：O(x * n)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n;
    cin >> x >> n;
    vector<int> value(n);
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    // 按面值排序
    sort(value.begin(), value.end());

    // 必须有面值为1的硬币，否则无法保证连续性
    if (value[0] != 1) {
        cout << -1 << endl;
        return 0;
    }

    int ok = 0;   // 当前已经能凑出 [1, ok] 范围内的所有值
    int res = 0;  // 使用的硬币数

    while (ok < x) {
        // 选择不超过 ok+1 的最大硬币（贪心策略）
        int coin = 0;
        for (int v : value) {
            if (v <= ok + 1) {  // 当前需要凑出 ok+1
                coin = v;       // 选择最大的可用硬币
            } else {
                break;
            }
        }

        // 无法继续扩展
        if (coin == 0) {
            cout << -1 << endl;
            return 0;
        }

        // 使用这枚硬币后，可达范围扩展到 [1, ok+coin]
        ok += coin;
        res++;
    }

    cout << res << endl;
    return 0;
}