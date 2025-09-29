#include <bits/stdc++.h>
using namespace std;

bool contain1(long long n);
bool contain0(long long n);

int main() {
    long long k, t, m;
    cin >> k >> t >> m;
    int res1 = 0, res2 = 0, res3 = 0;
    long long next = 1;
    for (long long i = 1; i <= k; i++) {
        if (contain1(next) && contain0(next)) {
            res3++;
        } else if (contain1(next)) {
            res1++;
        } else if (contain0(next)) {
            res2++;
        }
        next = (next + t) % m;
    }
    cout << res1 << " " << res2 << " " << res3 << endl;
    return 0;
}

bool contain1(long long n) {
    while (n > 0) {
        if (n % 10 == 1) {
            return true;
        }
        n /= 10;
    }
    return false;
}

bool contain0(long long n) {
    while (n > 0) {
        if (n % 10 == 0) {
            return true;
        }
        n /= 10;
    }
    return false;
}