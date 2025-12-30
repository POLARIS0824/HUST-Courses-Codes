// https://www.luogu.com.cn/problem/P1250 种树
// 核心思路：多个区间种树要求，满足所有要求的前提下使总树数最少
// 算法：贪心 + 区间排序
// 策略：按右端点排序，对每个区间优先从右往左种树（为后续区间留出更多空间）
// 时间复杂度：O(h * n)，h 为区间数，n 为道路长度

#include <bits/stdc++.h>
using namespace std;

struct request {
    int b, e, t;  // 左端点，右端点，最少树数
    // 按右端点排序，运算符重载
    bool operator<(const request& other) const {
        return e < other.e;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<request> requests(h);
    for (int i = 0; i < h; ++i) {
        cin >> requests[i].b >> requests[i].e >> requests[i].t;
    }

    // 按右端点排序（贪心策略的关键）
    sort(requests.begin(), requests.end());

    vector<bool> hasTree(n + 1, false);  // 记录每个位置是否种树
    int totalT = 0;

    // 处理每个区间要求
    for (const auto& r : requests) {
        // 统计区间内已经种的树
        int existT = 0;
        for (int i = r.b; i <= r.e; ++i) {
            if (hasTree[i]) {
                existT++;
            }
        }

        // 计算还需要种多少树
        int need = r.t - existT;

        // 从右往左贪心种树（为后续区间留出更多选择空间）
        for (int i = r.e; i >= r.b && need > 0; --i) {
            if (!hasTree[i]) {
                hasTree[i] = true;
                totalT++;
                need--;
            }
        }
    }

    cout << totalT << endl;
    return 0;
}