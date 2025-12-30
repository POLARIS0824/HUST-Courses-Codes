// https://www.luogu.com.cn/problem/P1443 马的遍历
// 核心思路：计算国际象棋中马从起点到棋盘各点的最少步数
// 算法：BFS 多源最短路径
// 马的走法：日字形，8个方向
// 时间复杂度：O(n * m)

#include <bits/stdc++.h>
using namespace std;

int dist[512][512];  // 距离数组
int n, m, x, y;      // 棋盘大小和起点坐标

// 马的8个方向移动：日字形
int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

struct loc {
    int x, y;
};

void bfs() {
    queue<loc> q;
    q.push({x, y});
    dist[x][y] = 0;  // 起点距离为 0

    while (!q.empty()) {
        loc cur = q.front();
        q.pop();

        // 尝试马的8个方向
        for (int i = 0; i < 8; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            // 边界检查
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                if (dist[nx][ny] == -1) {  // 未访问过
                    dist[nx][ny] = dist[cur.x][cur.y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> x >> y;

    memset(dist, -1, sizeof(dist));  // -1 表示未访问
    bfs();

    // 输出结果
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}