// https://www.luogu.com.cn/problem/P1825 Corn Maze S

#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
char maze[512][512];
bool visited[512][512];
vector<pair<int, int>> portals[30];

int dx[] = {-1, 1, 0, 0};
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



        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (maze[nx][ny] == '#') continue;
            if (maze[nx][ny] == '=') {
                cout << cur.time + 1 << endl;
                return;
            }

            int x = nx;
            int y = ny;

            if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z') {
                int index = maze[nx][ny] - 'A';
                pair<int, int> p1 = portals[index][0];
                pair<int, int> p2 = portals[index][1];
                if (nx == p1.first && ny == p1.second) {
                    x = p2.first;
                    y = p2.second;
                } else {
                    x = p1.first;
                    y = p1.second;
                }
            }

            // 传送后再检查
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
                x = i;
                y = j;
            }
            else if (maze[i][j] >= 'A' && maze[i][j] <= 'Z') {
                portals[maze[i][j] - 'A'].push_back({i, j});
            }
        }
    }
    
    bfs();
    return 0;
}