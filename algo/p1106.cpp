// https://www.luogu.com.cn/problem/P1106 删数问题
// 核心思路：从高位到低位，尽量保持数字递增，删除较大的数字
// 算法：贪心 + 栈/字符串模拟栈
// 时间复杂度：O(n)，每个数字最多入栈和出栈各一次

#include <bits/stdc++.h>
using namespace std;

int main() {
    string n;
    int k;
    if (!(cin >> n)) {
        return 0;
    }
    if (!(cin >> k)) {
        return 0;
    }

    string a;  // 用字符串模拟栈
    a.reserve(n.size());

    // 贪心策略：从左到右遍历，维护单调递增序列
    for (char i : n) {
        // 如果栈顶元素比当前元素大，且还可以删除，则删除栈顶
        while (!a.empty() && k > 0 && a.back() > i) {
            a.pop_back(); // 删除栈顶（更大的数字）
            --k;          // 删除次数减1
        }
        a.push_back(i);   // 当前数字入栈
    }

    // 如果删除次数还没用完，从后面继续删除
    while (k > 0 && !a.empty()) {
        a.pop_back();
        --k;
    }

    // 去掉前导零
    size_t pos = a.find_first_not_of('0');
    if (pos == string::npos) {
        cout << 0; // 全是0的情况
    } else {
        cout << a.substr(pos) << endl;
    }
    return 0;
}