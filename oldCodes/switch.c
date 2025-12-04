#include <stdio.h>

unsigned short swapHighLow4Bits(unsigned short k) {
    // 提取高 4 位和低 4 位
    unsigned short high4 = (k & 0xF000) >> 12;
    unsigned short low4 = (k & 0x000F);
    
    // 清除原来的高 4 位和低 4 位
    k &= 0x0FF0;
    
    // 将高 4 位和低 4 位交换
    k |= (low4 << 12) | high4;
    
    return k;
}

int main() {
    unsigned short k;
    
    printf("请输入一个无符号短整数: ");
    if (scanf("%hu", &k) != 1) {
        printf("输入无效。\n");
        return 1;
    }
    
    unsigned short result = swapHighLow4Bits(k);
    printf("交换高4位和低4位后的结果: %hu\n", result);
    
    return 0;
}