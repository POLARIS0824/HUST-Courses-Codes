#include<stdio.h>
 /*判断x是否是完全数，是则返回1，否则返回0*/
int isPerfect(int x)
{
    int s = 0;
    for(int y = 1; y <= x/2; y++)
    {
        if(x % y == 0)
        {
            s += y;
        }
    }
    return s == x;
}
int main()
{
    int a;
    //printf("1000内的完数有：");
    for(a=1; a <= 1000; a++)    /*遍历所有数*/
        if(isPerfect(a))
        {
            printf("%d\n", a);
        }
    return 0;
}