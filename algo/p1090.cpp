// https://www.luogu.com.cn/problem/P1090 合并果子
// 核心思路：Huffman 树 - 每次合并最小的两堆，使得总代价最小
// 算法：贪心 + 优先队列（小根堆）
// 时间复杂度：O(n log n)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 使用小根堆（优先队列），每次取出最小的两堆
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        pq.push(temp);
    }

    int res = 0; // 累计总代价

    // 每次取出最小的两堆合并
    while (pq.size() > 1) {
        int a = pq.top(); // 最小堆
        pq.pop();
        int b = pq.top(); // 次小堆
        pq.pop();
        int sum = a + b;  // 合并后的新堆
        res += sum;       // 累加合并代价
        pq.push(sum);     // 将新堆放回优先队列
    }

    cout << res << endl;
    return 0;
}