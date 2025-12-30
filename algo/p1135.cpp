// https://www.luogu.com.cn/problem/P1135 奇怪的电梯
// 核心思路：每层楼只能上下移动固定的楼层数，求从起点到终点的最少按键次数
// 算法：BFS 最短路径
// 时间复杂度：O(n)

#include <bits/stdc++.h>
using namespace std;

int n, a, b;
int K[256];    // K[i] 表示第 i 层楼可以移动的楼层数
int dist[256]; // dist[i] 表示从起点到第 i 层的最少按键次数

void bfs() {
    if (a == b) {
        cout << 0 << endl;
        return;
    }

    queue<int> q;
    q.push(a);       // 起点入队
    dist[a] = 0;     // 起点距离为 0

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        // 尝试向上移动
        int up = cur + K[cur];
        if (up <= n)  {
            if (dist[up] == -1) {  // 未访问过
                dist[up] = dist[cur] + 1;
                if (up == b) {
                    cout << dist[up] << endl;
                    return;
                }
                q.push(up);
            }
        }

        // 尝试向下移动
        int down = cur - K[cur];
        if (down >= 1) {
            if (dist[down] == -1) {  // 未访问过
                dist[down] = dist[cur] + 1;
                if (down == b) {
                    cout << dist[down] << endl;
                    return;
                }
                q.push(down);
            }
        }
    }

    // 无法到达终点
    cout << -1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dist, -1, sizeof(dist));  // -1 表示未访问

    cin >> n >> a >> b;

    for (int i = 1; i <= n; ++i) {
        cin >> K[i];
    }

    bfs();
    return 0;
}