// https://www.luogu.com.cn/problem/P1443 马的遍历

#include <bits/stdc++.h>
using namespace std;

int dist[512][512];
int n, m, x, y;

int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

struct loc {
    int x, y;
};

void bfs() {
    queue<loc> q;
    q.push({x, y});
    dist[x][y] = 0;
    while (!q.empty()) {
        loc cur = q.front();
        q.pop();

        for (int i = 0; i < 8; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                if (dist[nx][ny] == -1) {
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

    memset(dist, -1, sizeof(dist));
    bfs();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}