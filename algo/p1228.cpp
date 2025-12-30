// https://www.luogu.com.cn/problem/P1228 地毯填补问题
// 核心思路：用 L 型瓷砖填补一个缺少一个方块的 2^k × 2^k 棋盘
// 算法：分治递归
// 关键：将棋盘分成四个象限，缺口所在的象限直接递归处理，其他三个象限在中心放置一块 L 型瓷砖后递归
// 时间复杂度：O(4^k)

#include <bits/stdc++.h>
using namespace std;

// x, y: 当前正方形的左上角坐标
// dx, dy: 缺口（特殊方块）的坐标
// len: 当前正方形的边长
void solve(int x, int y, int dx, int dy, int len) {
    if (len == 1) return;  // 递归边界：1×1 方格无需填补

    int half = len / 2;

    // 判断缺口在哪个象限，然后在其他三个象限的交界处放置一块 L 型瓷砖
    // 左上角象限 [x, x+half-1] × [y, y+half-1]
    if (dx <= x + half - 1 && dy <= y + half - 1) {
        // 缺口在左上角，在其他三个象限的交界处放置 L 型瓷砖（编号1）
        cout << x + half << " " << y + half << " " << "1" << endl;

        solve(x, y, dx, dy, half);                                  // 左上角（含缺口）
        solve(x, y + half, x + half - 1, y + half, half);           // 右上角
        solve(x + half, y, x + half, y + half - 1, half);           // 左下角
        solve(x + half, y + half, x + half, y + half, half);        // 右下角
    }

    // 右上角象限 [x, x+half-1] × [y+half, y+len-1]
    else if (dx <= x + half - 1 && dy > y + half - 1) {
        // 缺口在右上角，放置 L 型瓷砖（编号2）
        cout << x + half << " " << y + half - 1 << " " << "2" << endl;

        solve(x, y, x + half - 1, y + half - 1, half);              // 左上角
        solve(x, y + half, dx, dy, half);                           // 右上角（含缺口）
        solve(x + half, y, x + half, y + half - 1, half);           // 左下角
        solve(x + half, y + half, x + half, y + half, half);        // 右下角
    }

    // 左下角象限 [x+half, x+len-1] × [y, y+half-1]
    else if (dx > x + half - 1 && dy <= y + half - 1) {
        // 缺口在左下角，放置 L 型瓷砖（编号3）
        cout << x + half - 1 << " " << y + half << " " << "3" << endl;

        solve(x, y, x + half - 1, y + half - 1, half);              // 左上角
        solve(x, y + half, x + half - 1, y + half, half);           // 右上角
        solve(x + half, y, dx, dy, half);                           // 左下角（含缺口）
        solve(x + half, y + half, x + half, y + half, half);        // 右下角
    }

    // 右下角象限 [x+half, x+len-1] × [y+half, y+len-1]
    else {
        // 缺口在右下角，放置 L 型瓷砖（编号4）
        cout << x + half - 1 << " " << y + half - 1 << " " << "4" << endl;

        solve(x, y, x + half - 1, y + half - 1, half);              // 左上角
        solve(x, y + half, x + half - 1, y + half, half);           // 右上角
        solve(x + half, y, x + half, y + half - 1, half);           // 左下角
        solve(x + half, y + half, dx, dy, half);                    // 右下角（含缺口）
    }
}

int main() {
    int k;
    cin >> k;
    int x, y;
    cin >> x >> y;
    int len = 1 << k;  // 2^k

    solve(1, 1, x, y, len);
    return 0;
}