// https://www.luogu.com.cn/problem/P1228 地毯填补问题

#include <bits/stdc++.h>
using namespace std;

// 设 x, y 为当前处理的正方形左上角坐标
void solve(int x, int y, int dx, int dy, int len) {
    if (len == 1) return;

    int half = len / 2;

    // 左上角
    // [x..x+half-1] [y..y+half-1]
    if (dx <= x + half - 1 && dy <= y + half - 1) {
        // 填补剩余三个角
        cout << x + half << " " << y + half << " " << "1" << endl;

        solve(x, y, dx, dy, half);
        solve(x, y + half, x + half - 1, y + half, half); // 右上角
        solve(x + half, y, x + half, y + half - 1, half); // 左下角
        solve(x + half, y + half, x + half, y + half, half); // 右下角
    }

    // 右上角
    else if (dx <= x + half - 1 && dy > y + half - 1) {
        cout << x + half << " " << y + half -1 << " " << "2" << endl;

        solve(x, y, x + half - 1, y + half - 1, half);
        solve(x, y + half, dx, dy, half);
        solve(x + half, y, x + half, y + half - 1, half);
        solve(x + half, y + half, x + half, y + half, half);
    }

    // 左下角
    else if (dx > x + half - 1 && dy <= y + half - 1) {
        cout << x + half - 1 << " " << y + half << " " << "3" << endl;
        
        solve(x, y, x + half - 1, y + half - 1, half);
        solve(x, y + half, x + half - 1, y + half, half);
        solve(x + half, y, dx, dy, half);
        solve(x + half, y + half, x + half, y + half, half);
    }

    // 右下角
    else {
        cout << x + half - 1 << " " << y + half - 1 << " " << "4" << endl;

        solve(x, y, x + half - 1, y + half - 1, half);
        solve(x, y + half, x + half - 1, y + half, half);
        solve(x + half, y, x + half, y + half - 1, half);
        solve(x + half, y + half, dx, dy, half);
    }
}

int main() {
    int k;
    cin >> k;
    int x, y;
    cin >> x >> y;
    int len = 1 << k; // 2 ^ k

    solve(1, 1, x, y, len);
    return 0;
}