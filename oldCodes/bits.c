#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned bit0 : 1;
    unsigned bit1 : 1;
    unsigned bit2 : 1;
    unsigned bit3 : 1;
    unsigned bit4 : 1;
    unsigned bit5 : 1;
    unsigned bit6 : 1;
    unsigned bit7 : 1;
} bits;

// 合并为一个通用函数
void call_function(int bit_position)
{
    printf("the function %d is called!\n", bit_position);
}

int main()
{
    unsigned int n;
    scanf("%u", &n);
    
    // 使用循环检查每一位
    for(int i = 0; i < 8; i++) {
        if(n & (1 << i)) {
            call_function(i);
        }
    }
    
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct 
// {
//     unsigned bit0 : 1;
//     unsigned bit1 : 1;
//     unsigned bit2 : 1;
//     unsigned bit3 : 1;
//     unsigned bit4 : 1;
//     unsigned bit5 : 1;
//     unsigned bit6 : 1;
//     unsigned bit7 : 1;
// } bits;

// void f0(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f1(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f2(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f3(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f4(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f5(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f6(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// void f7(int b)
// {
//     printf("the function %d is called!\n", b);
// }

// int main()
// {
//     unsigned int n;
//     scanf("%u", &n);
//     bits b;
//     b.bit0 = n & 1;
//     b.bit1 = (n >> 1) & 1;
//     b.bit2 = (n >> 2) & 1;
//     b.bit3 = (n >> 3) & 1;
//     b.bit4 = (n >> 4) & 1;
//     b.bit5 = (n >> 5) & 1;
//     b.bit6 = (n >> 6) & 1;
//     b.bit7 = (n >> 7) & 1;

//     void (*f[8])(int) = {f0, f1, f2, f3, f4, f5, f6, f7};
//     // 如果某一位是1，就调用对应的函数
//     if (b.bit0)
//         f[0](0);
//     if (b.bit1)
//         f[1](1);
//     if (b.bit2)
//         f[2](2);
//     if (b.bit3) 
//         f[3](3);
//     if (b.bit4)
//         f[4](4);
//     if (b.bit5)
//         f[5](5);
//     if (b.bit6)
//         f[6](6);
//     if (b.bit7)
//         f[7](7);
//     return 0;
// }