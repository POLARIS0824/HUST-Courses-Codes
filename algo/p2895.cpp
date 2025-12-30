// https://www.luogu.com.cn/problem/P2895 Meteor Shower S
// 核心思路：躲避流星雨，找到逃生路径
// 算法：BFS 最短路径 + 时间约束
// 关键：预处理每个位置被流星摧毁的时间，BFS时只能在摧毁前通过
// 特殊处理：流星撞击点及其四周都会被摧毁
// 时间复杂度：O(m + 坐标范围)

#include <bits/stdc++.h>
using namespace std;

int INF = 0x3f3f3f3f;

int m;
int crash[512][512];    // crash[i][j]: 位置(i,j)被摧毁的时间
int visited[512][512];  // 是否访问过

int dx[] = {0, -1, 1, 0, 0};  // 五个方向：中心、上、下、左、右
int dy[] = {0, 0, 0, -1, 1};

struct loc {
    int x, y, time;  // 到达该位置的时间
};

void bfs() {
    queue<loc> q;
    q.push({0, 0, 0});  // 从原点出发
    visited[0][0] = 1;

    // 特殊情况：起点在时刻0就被摧毁
    if (crash[0][0] == 0) {
        cout << -1 << endl;
        return;
    }

    while (!q.empty()) {
        loc cur = q.front();
        q.pop();

        // 到达安全区域（永远不会被摧毁的位置）
        if (crash[cur.x][cur.y] == INF) {
            cout << cur.time << endl;
            return;
        }

        // 尝试四个方向移动（不包括原地不动）
        for (int i = 1; i < 5; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            int ntime = cur.time + 1;

            // 边界检查 + 未访问 + 在摧毁前到达
            if (nx >= 0 && ny >= 0 && !visited[nx][ny]) {
                if (ntime < crash[nx][ny]) {
                    visited[nx][ny] = 1;
                    q.push({nx, ny, ntime});
                }
            }
        }
    }

    // 无法逃生
    cout << -1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化所有位置为永不摧毁
    memset(crash, 0x3f, sizeof(crash));

    cin >> m;
    while (m--) {
        int x, y, t;
        cin >> x >> y >> t;

        // 流星撞击点及其四周都会在时刻t被摧毁
        for (int i = 0; i < 5; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0) {
                // 如果多个流星撞击同一位置，取最早的时间
                crash[nx][ny] = min(crash[nx][ny], t);
            }
        }
    }

    bfs();
    return 0;
}