// https://www.luogu.com.cn/problem/P1250 种树
// 贪心

#include <bits/stdc++.h>
using namespace std;

struct request {
    int b, e, t; // 左右端点，最少树
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
    sort(requests.begin(), requests.end());
    
    vector<bool> hasTree(n + 1, false);
    int totalT = 0;
    for (const auto& r : requests) {
        int existT = 0; // 种了几颗
        for (int i = r.b; i <= r.e; ++i) {
            if (hasTree[i]) {
                existT++;
            }
        }
        int need = r.t - existT; // 还要种
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