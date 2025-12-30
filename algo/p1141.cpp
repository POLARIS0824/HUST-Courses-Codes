// https://www.luogu.com.cn/problem/P1141 01迷宫
// 核心思路：求连通块大小，相邻且数字不同的格子连通
// 算法：BFS 求连通块 + 记忆化优化
// 优化：每次BFS后将整个连通块的所有格子都标记为同一个大小，避免重复计算
// 时间复杂度：O(n^2)

#include <bits/stdc++.h>
using namespace std;

int n, m;
int maze[1024][1024];
int mem[1024][1024];      // 记录每个格子所在连通块的大小
bool visited[1024][1024]; // 记录是否访问过
vector<vector<int>> query;

int dx[] = {-1, 1, 0, 0};  // 四个方向：上下左右
int dy[] = {0, 0, -1, 1};

// BFS 求从 (r, c) 出发的连通块大小
int bfs(int r, int c) {
    if (mem[r][c] != -1) return mem[r][c];  // 已经计算过，直接返回

    queue<pair<int, int>> q;
    vector<pair<int, int>> cells; // 记录连通块内部所有格子

    q.push({r, c});
    visited[r][c] = true;
    cells.push_back({r, c});

    int res = 0;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        res++;

        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int nr = p.first + dx[i];
            int nc = p.second + dy[i];

            // 边界检查 + 未访问 + 数字不同（连通条件）
            if (nr >= 1 && nr <= n && nc >= 1 && nc <= n
                && !visited[nr][nc] && maze[nr][nc] != maze[p.first][p.second]) {

                visited[nr][nc] = true;
                q.push({nr, nc});
                cells.push_back({nr, nc});
            }
        }
    }

    // 记忆化：将连通块内所有格子都标记为同一个大小
    for (auto [r, c] : cells) {
        mem[r][c] = res;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            maze[i][j] = s[j - 1] - '0';  // 字符转数字
        }
    }

    memset(mem, -1, sizeof(mem));          // -1 表示未计算
    memset(visited, false, sizeof(visited));

    // 处理每个查询
    for (int i = 0; i < m; ++i) {
        int r, c;
        cin >> r >> c;
        cout << bfs(r, c) << endl;
    }

    return 0;
}