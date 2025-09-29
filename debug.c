#include <stdio.h>
#include <stdbool.h>

void josephus_last_person(int M, int N) {
    int a[M];        // 编号数组
    bool marked[M];  // 标记数组
    int i, count = 0, remaining = M; // 当前索引、计数器、剩余人数

    // 初始化数组
    for (i = 0; i < M; i++) {
        a[i] = i + 1;     // 编号从 1 到 M
        marked[i] = false; // 初始时所有人都未被移除
    }

    i = 0; // 从第一个人开始
    while (remaining > 1) { // 直到剩下最后一个人
        if (!marked[i]) { // 如果当前人未被移除
            count++;      // 计数
            if (count == N) { // 如果报数到 N
                marked[i] = true;  // 标记当前人
                count = 0;         // 重置计数器
                remaining--;       // 剩余人数减少
            }
        }
        i = (i + 1) % M; // 下一个人（循环队列）
    }

    // 找到最后剩下的人
    for (i = 0; i < M; i++) {
        if (!marked[i]) {
            printf("%d\n", a[i]); // 输出最后剩下的人的编号
            break;
        }
    }
}

int main() {
    int M, N;
    printf("Enter number of people (M) and step (N): ");
    scanf("%d %d", &M, &N);
    josephus_last_person(M, N);
    return 0;
}
