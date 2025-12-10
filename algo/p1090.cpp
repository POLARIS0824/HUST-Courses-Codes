// https://www.luogu.com.cn/problem/P1090 合并果子
// Huffman Tree

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        pq.push(temp);
    }

    int res = 0;
    while (pq.size() > 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        int sum = a + b;
        res += sum;
        pq.push(sum);
    }

    cout << res << endl;
    return 0;
}