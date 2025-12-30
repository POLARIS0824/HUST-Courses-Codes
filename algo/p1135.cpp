// https://www.luogu.com.cn/problem/P1135 奇怪的电梯

#include <bits/stdc++.h>
using namespace std;

int n, a, b;
int K[256];
int dist[256];

void bfs() {
    if (a == b) {
        cout << 0 << endl;
        return;
    }

    queue<int> q;
    q.push(a);
    dist[a] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int up = cur + K[cur];
        if (up <= n)  {
            // up
            if (dist[up] == -1) {
                dist[up] = dist[cur] + 1;
                if (up == b) {
                    cout << dist[up] << endl;
                    return;
                }
                q.push(up);
            }
        }

        int down = cur - K[cur];
        if (down >= 1) {
            // down
            if (dist[down] == -1) {
                dist[down] = dist[cur] + 1;
                if (down == b) {
                    cout << dist[down] << endl;
                    return;
                }
                q.push(down);
            }
        }
    }
    cout << -1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dist, -1, sizeof(dist));
    
    cin >> n >> a >> b;
    
    for (int i = 1; i <= n; ++i) {
        cin >> K[i];
    }

    bfs();
    return 0;
}