// https://www.luogu.com.cn/problem/P1434 滑雪
// 核心思路：在高度矩阵中找最长的下坡滑行路径
// 算法：DFS + 记忆化搜索（动态规划）
// 状态定义：mem[x][y] 表示从位置 (x, y) 出发能滑行的最大长度
// 优化：记忆化搜索避免重复计算子问题
// 时间复杂度：O(r * c)

#include <bits/stdc++.h>
using namespace std;

int r, c; // 行数和列数
vector<vector<int>> height; // 高度矩阵
vector<vector<int>> mem;    // 记忆化数组
int dx[] = {-1, 1, 0, 0};   // 四个方向：上下左右
int dy[] = {0, 0, -1, 1};

// DFS 求从 (x, y) 出发能滑行的最大长度
int dfs(int x, int y) {
    if (mem[x][y] != -1) {
        return mem[x][y];  // 已经计算过，直接返回
    }

    int maxLen = 1;  // 至少可以停在当前位置

    // 尝试向四个方向滑行
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 边界检查
        if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
            continue;
        }

        // 只能向更低的地方滑行
        if (height[nx][ny] < height[x][y]) {
            maxLen = max(maxLen, 1 + dfs(nx, ny));
        }
    }

    mem[x][y] = maxLen;  // 记忆化
    return maxLen;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c;
    height.resize(r, vector<int>(c));
    mem.resize(r, vector<int>(c, -1));  // -1 表示未计算

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> height[i][j];
        }
    }

    // 枚举所有起点，找最大值
    int res = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res = max(res, dfs(i, j));
        }
    }

    cout << res << endl;
    return 0;
}