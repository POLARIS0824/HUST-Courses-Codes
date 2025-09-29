#include <stdio.h>

int main()
{
    short k;
    short p;
    scanf("%hd%hd", &k, &p);

    // 提取 k 的高字节和 p 的低字节
    short high = (k & 0xFF00) >> 8;
    short low = (p & 0x00FF);

    // 如果 high 是负数，需要进行符号扩展
    if (high & 0x0080) {
        high |= 0xFF00;
    }

    // 合并高字节和低字节
    short a = (low << 8) | (high & 0x00FF);

    // 打印结果
    printf("%hd\n", a);

    return 0;
}