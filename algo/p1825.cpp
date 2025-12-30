// https://www.luogu.com.cn/problem/P1825 Corn Maze S
// 核心思路：带传送门的迷宫最短路径
// 算法：BFS 最短路径
// 特殊处理：遇到传送门字母时，直接传送到配对的另一个传送门位置
// 时间复杂度：O(n * m)

#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
char maze[512][512];
bool visited[512][512];
vector<pair<int, int>> portals[30];  // 存储每对传送门的两个位置

int dx[] = {-1, 1, 0, 0};  // 四个方向：上下左右
int dy[] = {0, 0, -1, 1};

struct loc {
    int x, y, time;
};

void bfs() {
    queue<loc> q;
    q.push({x, y, 0});
    visited[x][y] = true;

    while (!q.empty()) {
        loc cur = q.front();
        q.pop();

        // 尝试四个方向移动
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            // 边界检查
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (maze[nx][ny] == '#') continue;  // 障碍物

            // 到达终点
            if (maze[nx][ny] == '=') {
                cout << cur.time + 1 << endl;
                return;
            }

            int x = nx;
            int y = ny;

            // 处理传送门：如果是大写字母，传送到配对的另一个位置
            if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z') {
                int index = maze[nx][ny] - 'A';
                pair<int, int> p1 = portals[index][0];
                pair<int, int> p2 = portals[index][1];

                // 传送到另一个传送门
                if (nx == p1.first && ny == p1.second) {
                    x = p2.first;
                    y = p2.second;
                } else {
                    x = p1.first;
                    y = p1.second;
                }
            }

            // 传送后再检查是否访问过
            if (!visited[x][y]) {
                visited[x][y] = true;
                q.push({x, y, cur.time + 1});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == '@') {
                x = i;  // 起点
                y = j;
            }
            else if (maze[i][j] >= 'A' && maze[i][j] <= 'Z') {
                // 记录传送门位置
                portals[maze[i][j] - 'A'].push_back({i, j});
            }
        }
    }

    bfs();
    return 0;
}