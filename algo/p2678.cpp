// https://www.luogu.com.cn/problem/P2678 跳石头
// 核心思路：移除最多m块石头，使得跳跃的最小距离最大化
// 算法：二分答案 + 贪心验证
// 二分范围：最小跳跃距离的可能值 [1, L]
// 验证函数：贪心地移除距离小于mid的石头，检查移除数量是否<=m
// 时间复杂度：O(n * log L)

#include <bits/stdc++.h>
using namespace std;

int l, n, m; // l: 河的长度, n: 岩石数, m: 最多移除数
int rocks[60000];

bool isValid(int x);

int main() {
    cin >> l >> n >> m;
    rocks[0] = 0;        // 起点
    for (int i = 1; i <= n; ++i) {
        cin >> rocks[i];
    }
    rocks[n + 1] = l;    // 终点

    // 二分查找最小跳跃距离的最大值
    int low = 1;
    int high = l;
    int res = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isValid(mid)) {
            res = mid;      // mid可行，尝试更大的值
            low = mid + 1;
        } else {
            high = mid - 1;  // mid不可行，减小值
        }
    }

    cout << res << endl;
    return 0;
}

// 验证是否可以通过移除至多m块石头，使最小跳跃距离>=x
bool isValid(int x) {
    int remove = 0;      // 移除的石头数
    int prev = 0;        // 上一个保留的石头位置（起点）

    for (int i = 1; i <= n + 1; ++i) {
        // 如果当前石头距离上一个保留的石头太近，移除它
        if (rocks[i] - prev < x) {
            remove++;
            if (remove > m) {
                return false;  // 移除太多，不可行
            }
        } else {
            prev = rocks[i];  // 保留这块石头
        }
    }
    return true;
}
