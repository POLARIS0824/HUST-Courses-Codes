#include<stdio.h>
 int main()
 {
     int count, max, x, t;
     //printf("请输入一个正数：");
     scanf("%d", &x);
     count = 0; //0的个数
     max = 0;   //最大数字
     while(x)   //当x不为0时执行循环体
     {
         t = x % 10;  //取x的最后一位数
         if(t == 0)
            count++;
         if(t > max)
            max = t;
         x = x/10;  //去掉x的最后一位数
     }
     printf("该数有%d个零,最大数字是%d\n", count, max);
     return 0;
 }