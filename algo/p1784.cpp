// https://www.luogu.com.cn/problem/P1784 数独

#include <bits/stdc++.h>
using namespace std;

int grid[9][9];
bool row[9][10], col[9][10], cube[9][10];

bool dfs() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                int k = (i / 3) * 3 + j / 3;
                for (int x = 1; x <= 9; x++) {
                    if (!row[i][x] && !col[j][x] && !cube[k][x]) {
                        grid[i][j] = x;
                        row[i][x] = col[j][x] = cube[k][x] = true;

                        if (dfs()) return true;

                        grid[i][j] = 0;
                        row[i][x] = col[j][x] = cube[k][x] = false;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// bool canPut(int r, int c, int x) {
//     // row
//     for (int i = 0; i < 9; i++) {
//         if (grid[r][i] == x) return false;
//     }

//     // col
//     for (int j = 0; j < 9; j++) {
//         if (grid[j][c] == x) return false;
//     }

//     // 3 * 3 cube
//     int nr = (r / 3) * 3;
//     int nc = (c / 3) * 3;
//     for (int i = nr; i < nr + 3; i++) {
//         for (int j = nc; j < nc + 3; j++) {
//             if (grid[i][j] == x) return false;
//         }
//     }

//     return true;
// }

// bool dfs() {
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             if (grid[i][j] == 0) {
//                 for (int x = 1; x <= 9; x++) {
//                     if (canPut(i, j, x)) {
//                         grid[i][j] = x;
//                         if (dfs()) return true;
//                         grid[i][j] = 0;
//                     }
//                 }
//                 return false;
//             }
//         }
//     }
//     return true;
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) {
                int k = (i / 3) * 3 + j / 3;
                row[i][grid[i][j]] = true;
                col[j][grid[i][j]] = true;
                cube[k][grid[i][j]] = true;
            }
        }
    }
    
    dfs();
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << grid[i][j];
            if (j < 8) cout << " ";
        }
        cout << endl;
    }
    return 0;
}