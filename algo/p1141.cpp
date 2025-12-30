// https://www.luogu.com.cn/problem/P1141 01迷宫
// 联通块问题

#include <bits/stdc++.h>
using namespace std;

int n, m;
int maze[1024][1024];
int mem[1024][1024]; // 记录连通块大小
bool visited[1024][1024];
vector<vector<int>> query;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(int r, int c) {
    if (mem[r][c] != -1) return mem[r][c];

    queue<pair<int, int>> q;
    vector<pair<int, int>> cells; // 记录连通块内部格子

    q.push({r, c});
    visited[r][c] = true;
    cells.push_back({r, c});

    int res = 0;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        res++;

        for (int i = 0; i < 4; i++) {
            int nr = p.first + dx[i];
            int nc = p.second + dy[i];
            if (nr >= 1 && nr <= n && nc >= 1 && nc <= n 
                && !visited[nr][nc] && maze[nr][nc] != maze[p.first][p.second]) {
                
                visited[nr][nc] = true;
                q.push({nr, nc});
                cells.push_back({nr, nc});
            }
        }
    }
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
        string s; // !!!
        cin >> s;
        for (int j = 1; j <= n; j++) {
            maze[i][j] = s[j - 1] - '0';
        }
    }
    
    memset(mem, -1, sizeof(mem));
    memset(visited, false, sizeof(visited));
    
    for (int i = 0; i < m; ++i) {
        int r, c;
        cin >> r >> c;
        cout << bfs(r, c) << endl;
    }
    return 0;
}