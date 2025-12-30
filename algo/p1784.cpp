// https://www.luogu.com.cn/problem/P1784 数独
// 核心思路：用回溯法填充9×9数独，满足行、列、3×3方格的约束
// 算法：回溯 + 剪枝优化
// 优化：使用布尔数组快速判断数字是否可用（避免重复遍历检查）
// 时间复杂度：O(9^(空格数))，但实际通过剪枝大幅优化

#include <bits/stdc++.h>
using namespace std;

int grid[9][9];
bool row[9][10], col[9][10], cube[9][10];  // 记录行/列/方格中数字是否已使用

// 回溯搜索填充数独
bool dfs() {
    // 按行列顺序找到第一个空格
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                int k = (i / 3) * 3 + j / 3;  // 计算所在 3×3 方格的编号

                // 尝试填入 1-9
                for (int x = 1; x <= 9; x++) {
                    // 检查行、列、方格是否可以放置 x
                    if (!row[i][x] && !col[j][x] && !cube[k][x]) {
                        grid[i][j] = x;
                        row[i][x] = col[j][x] = cube[k][x] = true;

                        if (dfs()) return true;  // 递归填充下一个空格

                        // 回溯
                        grid[i][j] = 0;
                        row[i][x] = col[j][x] = cube[k][x] = false;
                    }
                }
                return false;  // 所有数字都尝试过，无解
            }
        }
    }
    return true;  // 所有格子都填满了
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入数独并标记已使用的数字
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) {
                int k = (i / 3) * 3 + j / 3;  // 方格编号
                row[i][grid[i][j]] = true;
                col[j][grid[i][j]] = true;
                cube[k][grid[i][j]] = true;
            }
        }
    }

    dfs();

    // 输出结果
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << grid[i][j];
            if (j < 8) cout << " ";
        }
        cout << endl;
    }
    return 0;
}