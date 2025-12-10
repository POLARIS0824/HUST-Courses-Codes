// https://www.luogu.com.cn/problem/P2018 消息传递

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1005;
vector<int> adj[MAX];
int n;

int dfs(int u, int father) {
    // 用 father 防止再次循环到自己
    vector<int> branches;
    for (int v : adj[u]) {
        if (v != father) {
            branches.push_back(dfs(v, u));
        }
    }
    // 叶子节点
    if (branches.empty()) {
        return 0;
    }
    // 贪心
    sort(branches.begin(), branches.end(), greater<int>());

    int max_t = 0;
    for (int i = 0; i < branches.size(); ++i) {
        max_t = max(max_t, branches[i] + i + 1);
    }
    return max_t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) {
        return 0;
    }

    if (n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }

    for (int i = 2; i <= n; ++i) {
        int father;
        cin >> father;
        adj[i].push_back(father);
        adj[father].push_back(i);
    }

    int min = 1e9;
    vector<int> best;
    for (int i = 1; i <= n; ++i) {
        int t = dfs(i, 0);
        if (t < min) {
            min = t;
            best.clear();
            best.push_back(i);
        } else if (t == min) {
            best.push_back(i);
        }
    }

    cout << min + 1 << endl;
    for (int i = 0; i < best.size(); ++i) {
        cout << best[i] << (i == best.size() - 1 ? "" : " ");
    }
    cout << endl;
    return 0;
}