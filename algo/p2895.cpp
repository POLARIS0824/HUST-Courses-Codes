// https://www.luogu.com.cn/problem/P2895 Meteor Shower S

#include <bits/stdc++.h>
using namespace std;

int INF = 0x3f3f3f3f;

int m;
int crash[512][512]; // 最早在哪一时刻撞击或烧焦 
int visited[512][512];

int dx[] = {0, -1, 1, 0, 0};
int dy[] = {0, 0, 0, -1, 1};

struct loc {
    int x, y, time; // 到达该位置的时间
};

void bfs() {
    queue<loc> q;
    q.push({0, 0, 0});
    visited[0][0] = 1;

    if (crash[0][0] == 0) {
        cout << -1 << endl;
        return;
    }

    while (!q.empty()) {
        loc cur = q.front();
        q.pop();

        if (crash[cur.x][cur.y] == INF) {
            cout << cur.time << endl;
            return;
        }

        for (int i = 1; i < 5; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            int ntime = cur.time + 1;

            if (nx >= 0 && ny >= 0 && !visited[nx][ny]) {
                if (ntime < crash[nx][ny]) {
                    visited[nx][ny] = 1;
                    q.push({nx, ny, ntime});
                }
            }
        }
    }
    cout << -1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(crash, 0x3f, sizeof(crash));

    cin >> m;
    while (m--) {
        int x, y, t;
        cin >> x >> y >> t;

        for (int i = 0; i < 5; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0) {
                crash[nx][ny] = min(crash[nx][ny], t);
            }
        }
    }

    bfs();
    return 0;
}