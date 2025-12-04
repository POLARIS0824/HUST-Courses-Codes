#include <bits/stdc++.h>
using namespace std;

// int main() {
//     int n, c;
//     cin >> n >> c;
//     vector<int> x(n);
//     for (int i = 0; i < n; i++) {
//         cin >> x[i];
//     }
//     // 1, 2, 8, 4, 9
//     // 1, 2, 4, 8, 9
//     // (1 + 4) / 2 = 2.5, 2, abs 2 - 2.5 = 0.5
//     // (4 + 9) / 2 = 6.5, 8, abs 8 - 6.5 = 1.5
//     // 0, 1, 2, 3, 4
//     // first 1, 9
//     // then (1 + 9) / 2 = 5, find a number that is closest to 5
//     sort(x.begin(), x.end());
//     int l = 0, r = n - 1;
//     if (c == 2) {
//         cout << x[r] - x[l] << endl;
//     }
//     else {
//         int res = INT_MAX;
//         while (c > 2) {
//             c--;
//             int mid = (x[l] + x[r]) / 2;
//             int min_diff = INT_MAX;
//             int min_diff_idx = -1;
//             for (int i = l + 1; i <= r - 1; i++) {
//                 int diff = abs(x[i] - mid);
//                 if (diff < min_diff) {
//                     min_diff = diff;
//                     min_diff_idx = i;
//                 }
//             }
//             res = min(abs(x[min_diff_idx] - x[l]), abs(x[min_diff_idx] - x[r]));
//             if (x[min_diff_idx] < mid) {
//                 l = min_diff_idx;
//             }
//             else {
//                 r = min_diff_idx;
//             }
//         }
//         cout << res << endl;
//     }
// }


bool isRight(int dist, int c, const vector<int>& x) {
    int count = 1;
    int last_pos = x[0];
    for (int i = 1; i < x.size(); ++i) {
        if (x[i] - last_pos >= dist) {
            count++;
            last_pos = x[i];
        }
    }
    return count >= c;
}

int main() {
    int n, c;
    cin >> n >> c;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sort(x.begin(), x.end());

    int l = 0, most = x[n - 1] - x[0];
    int ans = 0;

    while (l <= most) {
        int mid = l + (most - l) / 2;
        if (isRight(mid, c, x)) {
            ans = mid;
            l = mid + 1;
        } else {
            most = mid - 1;
        }
    }

    cout << ans << endl;

    return 0;
}