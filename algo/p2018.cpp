// https://www.luogu.com.cn/problem/P2018 消息传递
// 核心思路：在树中找到最优的消息源节点，使得消息传播到所有节点的时间最短
// 算法：DFS + 贪心
// 策略：对每个节点，优先向传播时间长的子树发送消息
// 关键：对于每个节点作为根，计算其最大传播时间 = max(子树传播时间 + 该子树的优先级)
// 时间复杂度：O(n^2)

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1005;
vector<int> adj[MAX];  // 邻接表
int n;

// 计算以u为根节点时的最大传播时间
// father: 父节点，用于防止回环
int dfs(int u, int father) {
    vector<int> branches;  // 存储所有子树的传播时间

    // 遍历所有相邻节点
    for (int v : adj[u]) {
        if (v != father) {  // 避免回到父节点
            branches.push_back(dfs(v, u));
        }
    }

    // 叶子节点：没有子树
    if (branches.empty()) {
        return 0;
    }

    // 贪心策略：按传播时间降序排序，优先向传播时间长的子树发送消息
    sort(branches.begin(), branches.end(), greater<int>());

    // 计算最大传播时间
    int max_t = 0;
    for (int i = 0; i < branches.size(); ++i) {
        // 第i个子树的传播时间 = 该子树的最大传播时间 + 发送顺序(i+1)
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

    // 特殊情况：只有一个节点
    if (n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }

    // 读入树结构（每个节点2到n的父节点）
    for (int i = 2; i <= n; ++i) {
        int father;
        cin >> father;
        adj[i].push_back(father);
        adj[father].push_back(i);  // 无向边
    }

    // 枚举每个节点作为消息源
    int min_time = 1e9;
    vector<int> best;
    for (int i = 1; i <= n; ++i) {
        int t = dfs(i, 0);  // 计算以i为根的传播时间
        if (t < min_time) {
            min_time = t;
            best.clear();
            best.push_back(i);
        } else if (t == min_time) {
            best.push_back(i);
        }
    }

    // 输出结果（传播时间需要+1，因为包含起始时刻）
    cout << min_time + 1 << endl;
    for (int i = 0; i < best.size(); ++i) {
        cout << best[i] << (i == best.size() - 1 ? "" : " ");
    }
    cout << endl;
    return 0;
}