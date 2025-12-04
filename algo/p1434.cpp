// https://www.luogu.com.cn/problem/P1434 滑雪

#include <bits/stdc++.h>
using namespace std;

int r, c; // row & col
vector<vector<int>> height;
vector<vector<int>> mem;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int dfs(int x, int y) {
    if (mem[x][y] != -1) {
        return mem[x][y];
    }
    int maxLen = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
            continue;
        }
        if (height[nx][ny] < height[x][y]) {
            maxLen = max(maxLen, 1 + dfs(nx, ny)); 
        }
    }
    mem[x][y] = maxLen;
    return maxLen;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c;
    height.resize(r, vector<int>(c));
    mem.resize(r, vector<int>(c, -1));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> height[i][j];
        }
    }
    int res = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res = max(res, dfs(i, j));
        }
    }
    cout << res << endl;
    return 0;
}